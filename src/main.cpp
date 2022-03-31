#include <Arduino.h>
#include "sensor_reading.h" // this inclusion will link the two files together.
#include <settings.h>

Adafruit_BME280 bme; //I2C


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);

  bool status;

  status = bme.begin(0x76);

  if(!status){
    Serial.println("Could not find valid BME280 sensor, check wiring");
    while(1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  refresh_reading(bme);
  delay(2000);
}


