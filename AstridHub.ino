/*
================================================================================

  AstridHub Firmware

  (c) 2018-2019 Astrid Innovations

================================================================================
*/

#include "AstridHub.h"

AstridHub hub;

void onNewGPSData(int data) {
	Serial.print("GPIO Value: ");
	Serial.println(data);
}

void onPushButtom(int value) {
	Serial.print("Buttom pressed: ");
	Serial.println(value);
}

void setup() {
    hub.start();
}

void loop(){
	hub.touch();
}




