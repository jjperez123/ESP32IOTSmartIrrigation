
#include <Arduino.h>

#include "sensor_reading.h"


// Collects and sends sensor reading to adaruit IO and Lora radio and display it on screen
// 
    void refresh_readings(Adafruit_BME280* bme, 
                          TFT_eSPI*        tft,
                          AdafruitIO_Feed* temp,
                          AdafruitIO_Feed* hum,
                          AdafruitIO_Feed* bar,
                          AdafruitIO_Feed* alt,
                          AdafruitIO_Feed* logger,
                          AdafruitIO_Feed* soil){
  float f_temperature;
  float f_humitidity;
  float f_pressure;
  float f_altitude;
  float f_moisture;

  tft->loadFont("RobotoSerif-36");
  tft->setRotation(1);
  uint16_t bg = TFT_BLACK;
  uint16_t fg = TFT_WHITE;

  tft->setCursor(5, 5);
  tft->setTextColor(fg, bg);
  tft->println("Right now...");

  //digitalWrite(LED_PIN, HIGH);

  f_temperature = bme->readTemperature();
  f_humitidity  = bme->readHumidity();
  f_pressure    = bme->readPressure() / 100.0F;
  f_altitude    = bme->readAltitude(SEALEVELPRESSURE_HPA);
  f_moisture        = moisture_LVL(SOIL_PIN);


  tft->setTextColor(TFT_YELLOW, bg);
  

  // Temperature
  Serial.print(f_temperature);
  Serial.println("  C");
  tft->fillRect(5,50,140,30,bg);
  tft->setCursor(5,50);
  tft->print(f_temperature);
  tft->println(" C");

  //Humidity
  Serial.print(f_humitidity);
  Serial.println(" %");
  tft->fillRect(5,90,130,30,bg);
  tft->setCursor(5,90);
  tft->print(f_humitidity);
  tft->println(" %");

  //Pressure
  Serial.print(f_pressure);
  Serial.println(" hpa");
  tft->fillRect(5,130,200,30,bg);
  tft->setCursor(5,130);
  tft->print(f_pressure);
  tft->println(" hpa");

// altitude is not really usefull
  // // Appx altitude
  // Serial.print(f_altitude);
  // Serial.println(" m");
  // tft->fillRect(5,170,200,30,bg);
  // tft->setCursor(5,170);
  // tft->print(f_altitude);
  // tft->println(" m");

  // Soil Moisture level
  Serial.print(f_moisture);
  Serial.println(" %");
  tft->fillRect(5,170,200,30,bg);
  tft->setCursor(5,170);
  tft->print(f_moisture);
  tft->println(" %");

  // Send data to Adafruit.IO
  temp ->save(f_temperature);
  hum ->save(f_humitidity);
  bar ->save(f_pressure);
  soil ->save(f_moisture);
  //alt ->save(alt);

  LoRa_sender(f_temperature, f_humitidity, f_pressure,f_altitude,f_moisture);

  // Update the postsCounter value in the EEPROM and the TFT
  postsCounter(tft,logger);
  tft->fillRect(180,0,10,10, TFT_BLACK);

  digitalWrite(LED_PIN, LOW);
  Serial.println("----------------");

}


/*
  Return the dirt moisture level.
*/
 int moisture_LVL(int PIN)
 {
   float analogReading = 0;
   analogReading = analogRead(SOIL_PIN); // read sensor
   analogReading = map(analogReading, AIR_VALUE, WET_VALUE,0,100);
   return analogReading;
 }

// Transmit data thorugh Lora Radio
  void LoRa_sender(float f_temperature, 
                  float f_humidity, 
                  float f_pressure, 
                  float f_altitude, 
                  float f_moisture)
  {
  Serial.print("Sending packet: ");
  // send packet
  LoRa.beginPacket();
  LoRa.print("temp(C) :");
  LoRa.println(String(f_temperature));
  delay(1000);
  LoRa.print("hum(%) :");
  LoRa.println(f_humidity);
  delay(1000);
  LoRa.print("press(hpa) :");
  LoRa.println(f_pressure);
  //delay(1000);
 //LoRa.print("alt :");
  //LoRa.println(f_altitude);
  delay(1000);
  LoRa.print("moist(%) :");
  LoRa.println(f_moisture);
  delay(1000);
  LoRa.endPacket();
  delay(1000);
  LoRa.sleep();
  }