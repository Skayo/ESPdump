#include "DDNS.h"

unsigned long ddnsUpdateTimer = millis();

int ddnsUpdate() {
	int updated = 0;

	Serial.print("Sending DDNS update request...");

	// send the request, retry on error
	int updateretries = 0;
	do {
		HTTPClient http;

		http.begin(DDNS_UPDATE_URL);

		int httpCode = http.GET();

		if (httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			if (payload == "OK")
				updated = 1;
		}

		http.end();
		updateretries++;

		if (updateretries < DDNS_ONERRORRETRIES && updated == 0)
			delay(1);
	} while (updated == 0 && updateretries < DDNS_ONERRORRETRIES);

	// check the status update
	if (updated) {
		Serial.println("DDNS update success");
	} else {
		Serial.println("DDNS update error");
	}

	return updated;
}

void ddnsCheckUpdate() {
	if (millis() > ddnsUpdateTimer) {
		ddnsUpdateTimer = millis() + DDNS_INTERVAL * 60 * 1000;
		if (!ddnsUpdate()) {
			ddnsUpdateTimer = millis() + DDNS_ONERRORINTERVAL * 60 * 1000;
		}
	}
}