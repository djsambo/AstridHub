#include "Utils.h"

const String CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

String Utils::UUID() {
    String uuid = "";
    for(int i=0;i<36;i++){
        if (i != 8 && i != 13 && i != 18 && i != 23) {
            uuid += CHARS[random(0, CHARS.length() - 1)];
        } else {
            uuid += "-";
        }
    }
    return uuid;
}

JSONObject Utils::emptyJSON(void) {
	JSONObject empty;
	return empty;
}
