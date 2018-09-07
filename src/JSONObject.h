#ifndef JSONObject_h
#define JSONObject_h

#include <WString.h>
#include <list>

class JSONObject {
public:
	JSONObject(void);
	JSONObject(String jsonValue);
	String getString(String key);
	int getInt(String key);
	float getFloat(String key);
	bool getBolean(String key);
	JSONObject getJSONObject(String key);

	void put(String key, String value);
	void put(String key, int value);
	void put(String key, float value);
	void put(String key, bool value);
	void put(String key, JSONObject value);

//	char* getChar(String key);
//	double getDouble(String key);
//	long getLong(String key);
//	short getShort(String key);
	String toString(void);
	std::list<String> getKeys(void);
	bool containsKey(String key);
	int size(void);
private:
	void createJSON(String jsonValue);

};

#endif
