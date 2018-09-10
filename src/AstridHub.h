/*
 * AstridHub.h
 *
 *  Created on: Sep 1, 2018
 *      Author: dsambo
 */

#ifndef ASTRIDHUB_H_
#define ASTRIDHUB_H_

#if defined(__AVR__)
#include "Arduino.h"
#elif defined(__PIC32MX__)
#include "WProgram.h"
#elif defined(__arm__)
#include "Arduino.h"
#endif

class AstridHub {
public:
	void start();
	void touch();
	void onDigitalRead(uint8_t port, void (*callback)(int));
	void onAnalogRead(uint8_t port, void (*callback)(int));
private:
	void dispathPinValue(uint8_t port, int value);
	void onInstruction();
	void openDBConnection();
	void startWiFiConnection();
	void checkInternetConnection();
	void verifyUpdates();
	void startWebServer();
	void openFirebaseEndPoint();
	void openClientEndPoint();
	void activateDevice();
	void releaseDevice();
	void createPreferenceProfile();
};

#endif /* ASTRIDHUB_H_ */
