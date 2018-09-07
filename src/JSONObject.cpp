/*
 * JSONObject.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: dsambo
 */

#include <JSONObject.h>
#include <Logbook.h>
#include <ArduinoJson.h>
#include <map>

std::map<String,String> data;
String jsonString;
extern Logbook logbook;

JSONObject::JSONObject(void) {
	createJSON("{}");
}

JSONObject::JSONObject(String jsonValue) {
	createJSON(jsonValue);
}

void JSONObject::createJSON(String jsonValue) {
	DynamicJsonBuffer djbJson;
	JsonObject& json = djbJson.parseObject(jsonValue);

	if (!json.success()) {
		logbook.error("The provided JSON value is invalid.");
	}

	for (auto kv : json) {
		data[kv.key] = kv.value.as<char*>();
	}

	json.printTo(jsonString);
}

String JSONObject::getString(String key) {
	return data[key];
}

int JSONObject::getInt(String key) {
	return data[key].toInt();
}

float JSONObject::getFloat(String key) {
	return data[key].toFloat();
}

bool JSONObject::getBolean(String key) {
	String d = data[key];
	d.toLowerCase();
	if (d.compareTo("true")) {
		return true;
	} else if (d.compareTo("false")) {
		return false;
	} else {
		logbook.error("This key value is not valid Boolean.");
	}
	return false;
}

JSONObject JSONObject::getJSONObject(String key) {
	JSONObject json(data[key]);
	return json;
}

void JSONObject::put(String key, String value) {
	data[key] = value;
}

void JSONObject::put(String key, int value) {
	String v(value);
	put(key, v);
}

void JSONObject::put(String key, float value) {
	String v(value);
	put(key, v);
}

void JSONObject::put(String key, bool value) {
	String v(value);
	put(key, v);
}

void JSONObject::put(String key, JSONObject value) {
	put(key, value.toString());
}

bool JSONObject::containsKey(String key) {
	return data.count(key) > 0;
}

int JSONObject::size() {
	return data.size();
}

std::list<String> JSONObject::getKeys() {
	std::list<String> keys;
	for (std::map<String, String>::iterator it = data.begin(); it != data.end();
			++it) {
		keys.push_back(it->first);
	}
	return keys;
}

String JSONObject::toString(void) {
	return jsonString;
}
