// The header files contain the declarations while the cpp file contain the implementations.

#ifndef SENSOR_READING_H
#define SENSOR_READINGS_H

    #include <Adafruit_Sensor.h>
    #include <Adafruit_BME280.h>
    #include "TFT_eSPI.h"

    #define SEALEVELPRESSURE_HPA (1013.25)

    // In h files you want to create declaration of the public functions that are available.
    void refresh_readings(Adafruit_BME280* bme, TFT_eSPI* tft); // Declare in the header so that the compiler knows about it is called in

#endif