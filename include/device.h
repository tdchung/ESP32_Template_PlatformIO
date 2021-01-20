#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Arduino.h"
#include <WebServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#include <WiFiUdp.h>
#include <HardwareSerial.h>

#include <ArduinoJson.h>

#include "WDevice.h"
#include "WNetwork.h"

#include <DHT.h>

#ifdef SIMULATION
#define DEFAULT_PUSH_DATA_TIME 60000
#define DEFAULT_UPDATE_DATA_TIME 10000
#else
#define DEFAULT_PUSH_DATA_TIME 60000
#define DEFAULT_UPDATE_DATA_TIME 10000
#endif

#ifdef TRAN_NPN
#define RELAY_ON HIGH
#define RELAY_OFF LOW
#else
#define RELAY_ON LOW
#define RELAY_OFF HIGH
#endif

#define LED_ON HIGH
#define LED_OFF LOW
// #else
// #define LED_ON LOW
// #define LED_OFF HIGH
// #endif

class Device : public WDevice
{
public:
	typedef std::function<void(void)> THandlerFunction;

	Device(WNetwork *network)
		: WDevice(network, "name", "name", DEVICE_TYPE_OZONE)

	{
		// sample init
		// this->isPIRinterrupted = false;
		// this->lastObjectDectedted = 0;

		// config LED pins
		// pinMode(LED_RED, OUTPUT);
		// pinMode(LED_GREEN, OUTPUT);
		// pinMode(LED_YELLOW, OUTPUT);
		// ...

		network->debug(F("Start config {...} sensor..."));
	}

	//----------------------------------------------------------------
	// MQTT handler
	void handleUnknownMqttCallback(bool getState, String completeTopic, String partialTopic, char *payload, unsigned int length)
	{
		// MQTT callback
	}

	//----------------------------------------------------------------
	// MAIN
	void loop(unsigned long now)
	{
	}

	// Public functions
	//----------------------------------------------------------------
	void setPirInterrupt(bool isInterrupt)
	{
		// code here
	}
	// ...

private:
	// private
	int pir_pin = 0;
	int dht_pin = 0;
	// ...

	// internal
	unsigned int _countDetect = 0;

	// private functions
	void notifyOnTimeUpdate()
	{
		// if (onTimeUpdate)
		// {
		// 	onTimeUpdate();
		// }
	}
	// ...
};

#endif
