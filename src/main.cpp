#include <Arduino.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BME280.h>

void refresh_reading(); // Declare in the header so that the compiler knows about it is called in

#ifndef LED_BUILTIN
  #define LED_BUILTIN 25 // this is valid for my devkit
#endif

#define SEALEVELPRESSURE_HPA (1013.25)
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
  refresh_reading();
  delay(2000);
}


