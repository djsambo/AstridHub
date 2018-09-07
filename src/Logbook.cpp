#include "Arduino.h"
#include "Logbook.h"

Logbook::Logbook(){
}

void Logbook::info(String message) {
    Serial.print("INFO: ");
    Serial.println(message);
}

void Logbook::warn(String message) {
    Serial.print("WARNING: ");
    Serial.println(message);   
}

void Logbook::error(String message) {
    Serial.print("ERROR: ");
    Serial.println(message);
//    throw message;
}
