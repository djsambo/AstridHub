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
#include <Thread.h>
#include <map>
#include <list>

Storage storage;
Logbook logbook;
Utils utils;
WiFiServer server(80);

std::map<uint8_t, int> lastDigitalPinsValue;
std::map<uint8_t, int> lastAnalogPinsValue;
std::map<uint8_t, std::list<void (*)(int)>> listenersPins;

void AstridHub::start() {
	Serial.begin(115200);
	Serial.println("STARTING");
	bool storageInitialized = storage.initialize();
	if (storageInitialized) {
		logbook.info("Database initialized.");
		startWiFiConnection();
	} else {
		logbook.error("An error was occurred on database initialization.");
	}
}

String prepareHtmlPage() {
	String htmlPage = String("HTTP/1.1 200 OK\r\n")
			+ "Content-Type: text/html\r\n" + "Connection: close\r\n"
			+ // the connection will be closed after completion of the response
			"Refresh: 5\r\n"
			+  // refresh the page automatically every 5 sec
			"\r\n" + "<!DOCTYPE HTML>" + "<html>" + "Analog input:  "
			+ String(analogRead(A0)) + "</html>" + "\r\n";
	return htmlPage;
}

void AstridHub::onDigitalRead(uint8_t pin, void (*callback)(int)) {
	pinMode(pin, INPUT);
	lastDigitalPinsValue[pin] = LOW;
	listenersPins[pin].push_back(callback);
}

void AstridHub::onAnalogRead(uint8_t pin, void (*callback)(int)) {
	pinMode(pin, INPUT);
	lastAnalogPinsValue[pin] = -1;
	listenersPins[pin].push_back(callback);
}

void AstridHub::dispathPinValue(uint8_t port, int value) {
	std::list<void (*)(int)> listeners = listenersPins[port];

	for (auto* listener : listeners) {
		listener(value);
	}
}

void AstridHub::touch() {
	for (std::map<uint8_t, int>::iterator it1 = lastDigitalPinsValue.begin();
			it1 != lastDigitalPinsValue.end(); ++it1) {
		int value = digitalRead(it1->first);
		if (value != it1->second) {
			lastDigitalPinsValue[it1->first] = value;
			dispathPinValue(it1->first, value);
		}
	}

	for (std::map<uint8_t, int>::iterator it2 = lastAnalogPinsValue.begin();
			it2 != lastAnalogPinsValue.end(); ++it2) {
		int value = analogRead(it2->first);
		if (value != it2->second) {
			lastAnalogPinsValue[it2->first] = value;
			dispathPinValue(it2->first, value);
		}
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
		WiFi.softAP("AstridHub", "admin12345678");
	}
	startWebServer();
}

void AstridHub::checkInternetConnection() {

}

void AstridHub::verifyUpdates() {

}

void AstridHub::startWebServer() {
	server.begin();
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

