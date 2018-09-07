/*
 * Response.cpp
 *
 *  Created on: Aug 26, 2018
 *      Author: dsambo
 */

#include <Response.h>

Response::Response(String payload) {
	this->isSuccess = true;
	this->payload = payload;
}

Response::Response(bool isSuccess, String message) {
	this->isSuccess = isSuccess;
	this->message = message;
}

Response::Response(bool isSuccess, String message, String payload) {
	this->isSuccess = isSuccess;
	this->message = message;
	this->payload = payload;
}

bool Response::success(void) {
	return this->isSuccess;
}

String Response::getMessage(void) {
	return this->message;
}

String Response::getString(void) {
	return this->payload;
}

bool Response::getBoolean(void) {
	return this->payload;
}

int Response::getInt(void) {
	return this->payload.toInt();
}

JSONObject Response::getJSONObject(void) {
	return JSONObject(this->payload);
}
