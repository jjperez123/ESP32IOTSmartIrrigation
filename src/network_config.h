# include<Arduino.h>

#define IO_USERNAME  "JJP24"
#define IO_KEY       "aio_wWIO72C2qdhQAjv0pJsqMgpBDy8t"

// home network credentials
#define WIFI_SSID  "PerezFamily"
#define WIFI_PASS  "05138690"

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME,IO_KEY,WIFI_SSID,WIFI_PASS);

