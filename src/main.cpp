#include <Arduino.h>
//#define DEBUGLOG
#include "settings.h"         // The order is important!
#include "sensor_reading.h"
#include "bmp_functions.h"
#include "TaskScheduler.h"
#include "network_config.h"



void sensor_readings_update();
void clock_update();
void update_indicators();

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;  // eastern time is GMT -5 hours * 60 minutes * 60 seconds
const int   daylightOffset_sec =3600; //3600;

Adafruit_BME280 bme; // I2C



TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

// Setup tasks for the task scheduler
// The third argument taks a pointer to a function, but cannot have parameters.
Task t1_bme280(30000, TASK_FOREVER, &sensor_readings_update);
Task t2_clock(1000,   TASK_FOREVER, &clock_update);
Task t5_indicators(2000, TASK_FOREVER, &update_indicators);

// Create the scheduler
Scheduler runner;

//Adafruit.IO feeds
//Avoid underscores in the feed names, they cause problems with grouping
AdafruitIO_WiFi io(IO_USERNAME,IO_KEY,WIFI_SSID,WIFI_PASS);
AdafruitIO_Feed *temperature =  io.feed("smart-farming.temperature");
AdafruitIO_Feed *humidity    =  io.feed("smart-farming.humidity");
AdafruitIO_Feed *barpressure =  io.feed("smart-farming.barpressure");
AdafruitIO_Feed *altitude    =  io.feed("smart-farming.altitude");
AdafruitIO_Feed *led_controller = io.feed("smart-farming.led");
AdafruitIO_Feed *aio_loger     = io.feed("smart-farming.logger");



void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(IFTTT_PIN,OUTPUT); // touch screen led
  Serial.begin(9600);

delay(500);

// Initializes the EPPROM
  EEPROM.begin(EEPROM_SIZE); // setup the EEPROM where we'll write and read the max number of
  //POSTs
  tft.println(EEPROM.readUInt(EEPROM_INDEX));

  if(EEPROM.readUInt(EEPROM_INDEX)<0)
  {
    EEPROM.writeUInt(EEPROM_INDEX,0); // if the value stored in EEPROM is negative, then initialise to zero
    EEPROM.commit();
  }

  delay(500);

  if (!SPIFFS.begin()) {
    tft.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  // Setup the TFT
  tft.begin();
  
  // Calibrate the touch interface
  // This only needs to be done once
  // The calibrate data will be stored in the SPIFS
  // It is importan to calibrate the touch interface after display is rotated.
  calibrate_touch_screen(&tft);

  tft.setRotation(1);
  tft.setTextColor(fg, bg);

  tft.fillScreen(bg);

  tft.setCursor(0, 0);
  tft.loadFont("NotoSansBold15");
  tft.println("Hello!");
  tft.println("Starting BME sensor...");
  delay(1000);

  bool status;

  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }


  // Check the wifi status and print on TFT
  wifiStatus(&tft,&io);

  // Connect to Wifi
  Serial.println("Connecting to Wifi...");
  io.connect();

  DEBUGPRINTLN("MQTT controller....");
  //set up a message handler for the count feed.
  //the handleMessage function (defined below)
  //will be called whenever a message is
  // received from adafruit io.
  led_controller->onMessage(ledMessage);
  
  // Check the Wifi status and update TFT
  wifiStatus(&tft, &io);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Check the Wifi status
  Serial.println(io.statusText());

  // Configure the clock.
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Start the task scheduler
  runner.init();

  // Add the task to the scheduler
  runner.addTask(t1_bme280);
  runner.addTask(t2_clock);
  runner.addTask(t5_indicators);
  // Enable the task
  t1_bme280.enable();
  t2_clock.enable();
  t5_indicators.enable();

  tft.fillScreen(bg); // clear the screen
  drawBmp("/te.bmp", 160, 198, &tft);

  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, TFT_BACKGROUND);
  tft.setCursor(230, 135);
  tft.print("HEAP MEM");
  
// Config WDT
   Serial.println("Configuring WDT...");
   esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
   esp_task_wdt_add(NULL); //add current thread to WDT watch

aio_loger -> save("Setup complete.");

}

void loop() {

    runner.execute();
    io.run(); 
    readTouch(&tft);
    esp_task_wdt_reset(); // feed the WDT
}

void sensor_readings_update()
{
  refresh_readings(&bme, 
                   &tft,
                  temperature,
                  humidity,
                  barpressure,
                  altitude,
                  aio_loger);
}


void clock_update()
{
  Serial.println(io.statusText());
  //printLocalTime();
  refresh_clock(&tft);
}

void update_indicators()
{
  indicators(&tft, &io);
}
