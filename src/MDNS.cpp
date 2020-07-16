#include "MDNS.h"

void mdnsSetup() {
	if (MDNS.begin(MDNS_HOST)) {
		MDNS.addService("http", "tcp", 80);

		Serial.println("MDNS responder started");
		Serial.print("You can now connect to http://");
		Serial.print(MDNS_HOST);
		Serial.println(".local");
	}
}

void mdnsUpdate() { MDNS.update(); }