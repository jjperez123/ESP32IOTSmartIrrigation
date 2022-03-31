// cpp files contain the implementation of our program while h files contains the declarations
#include <Arduino.h>
#include "settings.h"
#include "sensor_reading.h"



void refresh_reading(Adafruit_BME280 bme){
  float f_temperature;
  float f_humitidity;
  float f_pressure;
  float f_altitude;

  digitalWrite(LED_BUILTIN, HIGH);

  f_temperature = bme.readTemperature();
  f_humitidity  = bme.readHumidity();
  f_pressure    = bme.readPressure() / 100.0F;
  f_altitude    = bme.readAltitude(SEALEVELPRESSURE_HPA);

  // Temperature
  Serial.print(f_temperature);
  Serial.println("  C");

  //Humidity
  Serial.print(f_humitidity);
  Serial.println(" %");

  //Pressure
  Serial.print(f_pressure);
  Serial.println(" hpa");

  // Appx altitude
  Serial.print(f_altitude);
  Serial.println(" m");

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("----------------");

}