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
    #define LED_PIN  17
    #define IFTT_PIN 16
    #define EEPROM_SIZE 2 // We'll use 1 byte in the EEPROM to store the mac number of POSTs
    
#endif