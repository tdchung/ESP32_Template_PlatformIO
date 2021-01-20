// Framework Library
#include <Arduino.h>
#include <HardwareSerial.h>
#include "esp_system.h"

// Common Library
#include <DHT.h>

// App Library
#include "WNetwork.h"
#include "device.h"

// Define
#define APPLICATION "App_name"
#define VERSION "1.0.0"
#define DEBUG true

WNetwork *network = nullptr;

// device
Device *deviceName = nullptr;

// config sensors
/*
 *
 */

hw_timer_t *timer1 = NULL;

void IRAM_ATTR resetModule()
{
  ESP.restart();
}

void setup()
{
  // debug serial
  Serial.begin(9600);
  delay(2000);
  Serial.println("======== Start {NAME} firmware ========");

  //Wifi and Mqtt connection
  network = new WNetwork(DEBUG, APPLICATION, VERSION, true, NO_LED, 0x68);
  network->setOnNotify([]() {
    if (network->isWifiConnected())
    {
      //nothing to do
    }
    if (network->isMqttConnected())
    {
      //nothing to do;
    }
  });

  network->setOnConfigurationFinished([]() {
    // nothing to do
  });

  // watchdog
  timer1 = timerBegin(1, 80, true); //timer 0, div 80
  timerAttachInterrupt(timer1, &resetModule, true);
  timerAlarmWrite(timer1, 20000000, false); //set time in us
  timerAlarmEnable(timer1);                 //enable interrupt

  //Communication between ESP and Ozone Device
  deviceName = new Device(network);
  network->addDevice(deviceName);
}

void loop()
{
  timerWrite(timer1, 0); //reset timer (feed watchdog)
  network->loop(millis());
  delay(20);
}
