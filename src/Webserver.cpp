#include "Webserver.h"

ESP8266WebServer server(80);

static bool hasSD = false;
File uploadFile;

void webserverSetup() {
	server.on("/", HTTP_GET, showHomePage);
	//server.on("/list", HTTP_GET, printDirectory);
	//server.on("/edit", HTTP_DELETE, handleDelete);
	//server.on("/edit", HTTP_PUT, handleCreate);
	//server.on("/edit", HTTP_POST, []() { returnOK(); }, handleFileUpload);
	server.on("/create", HTTP_POST, []() { server.send(200); }, createDump);
	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");

	if (SD.begin(SS)) {
		Serial.println("SD Card initialized.");
		hasSD = true;
	}
}

void webserverHandleClient() { server.handleClient(); }

void showPage(String page) {
	File dataFile = SD.open(page.c_str());

	if (hasSD && dataFile) {
		if (server.streamFile(dataFile, "text/html") != dataFile.size()) {
			Serial.println("Sent less data than expected!");
		}

		dataFile.close();
		return;
	}

	server.sendHeader("Strict-Transport-Security", "max-age=0");
	server.send(404, "text/plain", "Couldn't load " + page);
	Serial.print("Couldn't load " + page);
}

void showHomePage() { return showPage("index.htm"); }

void handleNotFound() {
	if (server.uri() == "/create") {
		return server.send(200, "text/plain", "");
	}

	if (server.uri().startsWith("/dumps/")) {
		File dataFile = SD.open(server.uri().c_str());

		if (hasSD && dataFile) {
			if (server.streamFile(dataFile, "text/plain") != dataFile.size()) {
				Serial.println("Sent less data than expected!");
			}

			String filename = String(dataFile.name());
			dataFile.close();

			if (!server.hasArg("justCreated") && (filename.endsWith("yn") || filename.endsWith("yy"))) {  // If Self-Delete
				SD.remove(server.uri().c_str());
			}

			filename.clear();
			return;
		}

		Serial.print("Couldn't load " + server.uri());
		server.send(404, "text/plain", "");
		return;
	}

	return showPage("view.htm");
}

String generateID() {
	String id = "";
	byte randomValue = 0;
	char letter = 'a';

	for (int i = 0; i < 8; i++) {
		randomValue = random(0, 35);

		letter = randomValue + 'a';
		if (randomValue > 25)
			letter = (randomValue - 26) + '0';

		id += letter;
	}

	return id;
}

void createDump() {
	if (server.uri() != "/create") {
		return;
	}

	HTTPUpload &upload = server.upload();
	if (upload.status == UPLOAD_FILE_START) {
		String filename = "/dumps/" + generateID() + ".";

		// Generate file extension:

		if (server.hasArg("format") && (server.arg("format") == "m" || server.arg("format") == "p" || server.arg("format") == "s")) {
			filename += server.arg("format");
		} else {
			filename += "p";
		}

		if (server.hasArg("selfdel") && (server.arg("selfdel") == "y" || server.arg("selfdel") == "n")) {
			filename += server.arg("selfdel");
		} else {
			filename += "n";
		}

		if (server.hasArg("password") && (server.arg("password") == "y" || server.arg("password") == "n")) {
			filename += server.arg("password");
		} else {
			filename += "n";
		}

		uploadFile = SD.open(filename.c_str(), FILE_WRITE);
		Serial.print("Upload: START, filename: ");
		Serial.println(filename);

		filename.clear();
	} else if (upload.status == UPLOAD_FILE_WRITE) {
		if (uploadFile) {
			uploadFile.write(upload.buf, upload.currentSize);
		}
		Serial.print("Upload: WRITE, Bytes: ");
		Serial.println(upload.currentSize);
	} else if (upload.status == UPLOAD_FILE_END) {
		server.setContentLength(CONTENT_LENGTH_NOT_SET);
		if (uploadFile) {
			server.send(200, "application/json", "{\"filename\":\"" + String(uploadFile.name()) + "\"}");
			uploadFile.close();
		} else {
			server.send(500, "application/json", "{\"filename\":\"\"}");
		}
		Serial.print("Upload: END, Size: ");
		Serial.println(upload.totalSize);
	}
}