#include "WiFi.h"

IPAddress staticIP(192, 168, 1, 3);  // ESPdump Static IP
IPAddress gateway(192, 168, 1, 1);   // IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  // Subnet mask

void wifiSetup() {
	Serial.print("\n");
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	Serial.print("Connecting to ");
	Serial.println(WIFI_SSID);

	// Wait for connection
	uint8_t i = 0;
	while (WiFi.status() != WL_CONNECTED && i++ < 20) {  // wait 10 seconds
		delay(500);
	}

	if (i == 21) {
		Serial.print("Could not connect to");
		Serial.println(WIFI_SSID);

		while (1) {
			delay(500);
		}
	}

	WiFi.config(staticIP, gateway, subnet);

	Serial.print("Connected! IP address: ");
	Serial.println(WiFi.localIP());
}