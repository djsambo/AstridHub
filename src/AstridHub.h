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
      void onInstruction();
    private:
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
