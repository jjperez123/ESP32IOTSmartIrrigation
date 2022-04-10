#include <Arduino.h>
#include "sensor_reading.h" // this inclusion will link the two files together.
#include "settings.h"
#include "bmp_functions.h"


Adafruit_BME280 bme; //I2C

TFT_eSPI tft = TFT_eSPI();

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  
  if(!SPIFFS.begin()) {
    Serial.println("SPIFF initialisation failed!");
    while(1) yield(); // stay here twidddling thumbs waiting.
  }

  tft.init();

  tft.setRotation(1);
  tft.loadFont("RobotoSerif-36"); // Create TTF fonts using instructions at
  tft.setTextColor(fg,bg);
  tft.fillScreen(bg);

  tft.setCursor(0,0);
  tft.println("Hello!");
  tft.println("Starting BME sensor...");
  delay(5000);

  bool status;

  status = bme.begin(0x76);

  if(!status){
    Serial.println("Could not find valid BME280 sensor, check wiring");
    while(1);
  }
  tft.loadFont("NotoSansBold15");
  tft.fillScreen(bg); //Clear the screen
   drawBmp("/Logo.bmp",160,198, &tft);
}

void loop() {
  // put your main code here, to run repeatedly:
  refresh_readings(&bme, &tft);
  delay(2000);
}




