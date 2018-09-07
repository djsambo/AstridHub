/*
 * Error.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: dsambo
 */

#include <Error.h>

Error::Error(String message) {
	this->message = message;
	this->code = "NOR_SPECIFIED";
}

Error::Error(String code, String message) {
	this->code = code;
	this->message = message;
}

String Error::getCode(void) {
	return this->code;
}

String Error::getMessage(void) {
	return this->message;
}
