#include <Arduino.h>

#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <SD.h>
#include <SPI.h>

void webserverSetup();

void webserverHandleClient();

void showPage();

void showHomePage();

void handleNotFound();

String generateID();

void createDump();