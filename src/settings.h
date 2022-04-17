// this header file will contain the program settings.
#ifdef DEBUGLOG
#define DEBUGPRINT(x)       Serial.print(x)
#define DEBUGPRINTDEC(x)    Serial.print(x,DEC)
#define DEBUGPRINTLN(x)     Serial.print(x)
#else
#define DEBUGPRINT(x)
#define DEBUGPRINTDEC(x)
#define DEBUGPRINTLN(x)
#endif

#ifndef SETTINGS_H
#define SETTINGS_H
    #define LED_BUILTIN 2 // this is valid any devkit
    #include "TFT_eSPI.h"
    #include "AdafruitIO_WiFi.h"
    #include "network_config.h"
    #include "aux_functions.h"
    #include "clock.h"
    #include "EEPROM.h"
    #include "esp_system.h" // implementing the watchdog timer
    #include <esp_task_wdt.h>
    #include "mqtt_controller.h"
    #define LED_PIN     17
    #define IFTTT_PIN   16

    #define TFT_BACKGROUND     TFT_BLACK
    #define TFT_TEXT           TFT_WHITE


    #define EEPROM_SIZE 4 // We'll use 4 byte in the EEPROM to store the mac number of POSTs
    #define EEPROM_INDEX 0

    #define WDT_TIMEOUT 20
    #define CALIBRATION_FILE "/tft-touch-calData_1" // This file will contain the data from the
                                                  // touchscreen calibration process at boot (only needed once)
#endif