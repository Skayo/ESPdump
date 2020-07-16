#include <Arduino.h>

#include <ESP8266HTTPClient.h>

#define DDNS_UPDATE_URL "https://www.duckdns.org/update/espdump/<your-key-here>"
#define DDNS_ONERRORRETRIES 5
#define DDNS_ONERRORINTERVAL 1
#define DDNS_INTERVAL 60

int ddnsUpdate();

void ddnsCheckUpdate();