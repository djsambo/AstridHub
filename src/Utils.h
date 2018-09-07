#ifndef Utils_h
#define Utils_h

#include <JSONObject.h>
#include <Arduino.h>

class Utils {
public:
	String UUID(void);
	JSONObject emptyJSON(void);
};

#endif
