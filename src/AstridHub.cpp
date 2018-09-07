/*
 AstridHub.h - Library for provide house control.
 Created by Domingo J. Sambo, July 11, 2018.
 All right reserved.
 */

#include <Arduino.h>
#include <AstridHub.h>
#include <JSONObject.h>
#include <Logbook.h>
#include <Storage.h>
#include <Utils.h>
#include <ESP8266WiFi.h>
#include <Error.h>
#include <Response.h>

Storage storage;
Logbook logbook;
Utils utils;

void AstridHub::start() {
	Serial.begin(115200);
	bool storageInitialized = storage.initialize();
	if (storageInitialized) {
		logbook.info("Database initialized.");
		startWiFiConnection();
	} else {
		logbook.error("An error was occurred on database initialization.");
	}
}

void AstridHub::onInstruction() {

}

void AstridHub::startWiFiConnection() {
	Response response = storage.getRecord("configs", utils.emptyJSON());

	if (response.success()) {
		JSONObject configs = response.getJSONObject();
		Serial.println("Configs found.");
	} else {
		WiFi.begin("DAHouse", "Casada1440");

		Serial.print("Connecting");
		while (WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.print(".");
		}
		Serial.println();

		Serial.print("Connected, IP address: ");
		Serial.println(WiFi.localIP());
	}
}

void AstridHub::checkInternetConnection() {

}

void AstridHub::verifyUpdates() {

}

void AstridHub::startWebServer() {

}

void AstridHub::openFirebaseEndPoint() {

}

void AstridHub::openClientEndPoint() {

}

void AstridHub::activateDevice() {

}

void AstridHub::releaseDevice() {

}

void AstridHub::createPreferenceProfile() {

}

