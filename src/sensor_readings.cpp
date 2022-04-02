// cpp files contain the implementation of our program while h files contains the declarations
#include <Arduino.h>
#include "settings.h"
#include "sensor_reading.h"



void refresh_readings(Adafruit_BME280* bme, TFT_eSPI* tft){
  float f_temperature;
  float f_humitidity;
  float f_pressure;
  float f_altitude;

  uint16_t bg = TFT_BLACK;
  uint16_t fg = TFT_WHITE;
  
  digitalWrite(LED_BUILTIN, HIGH);

  f_temperature = bme->readTemperature();
  f_humitidity  = bme->readHumidity();
  f_pressure    = bme->readPressure() / 100.0F;
  f_altitude    = bme->readAltitude(SEALEVELPRESSURE_HPA);

  
  tft->setTextColor(TFT_YELLOW,bg);

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

  // Appx altitude
  Serial.print(f_altitude);
  Serial.println(" m");
  tft->fillRect(5,170,200,30,bg);
  tft->setCursor(5,170);
  tft->println(" m");

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("----------------");

}