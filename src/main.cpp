/*
  SDWebServer - Example WebServer with SD Card backend for esp8266

  Have a FAT Formatted SD Card connected to the SPI port of the ESP8266
  The web root is the SD Card root folder
  File extensions with more than 3 charecters are not supported by the SD
  Library File Names longer than 8 charecters will be truncated by the SD
  library, so keep filenames shorter index.htm is the default index (works on
  subfolders as well)

  upload the contents of SdRoot to the root of the SDcard and access the editor
  by going to http://esp8266sd.local/edit

*/
#include <Arduino.h>

#include "DDNS.h"
#include "MDNS.h"
#include "Webserver.h"
#include "WiFi.h"

void setup(void) {
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	randomSeed(analogRead(0));

	wifiSetup();

	//configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

	mdnsSetup();
	webserverSetup();
}

void loop(void) {
	webserverHandleClient();
	mdnsUpdate();
	ddnsCheckUpdate();
}