/*
 * Response.h
 *
 *  Created on: Aug 26, 2018
 *      Author: dsambo
 */

#ifndef SRC_RESPONSE_H_
#define SRC_RESPONSE_H_

#include <JSONObject.h>

class Response {
	String payload;
	String message;
	bool isSuccess;
public:
	Response(String payload);
	Response(bool isSuccess, String message);
	Response(bool isSuccess, String message, String payload);

	String getMessage(void);
	bool success(void);

	String getString(void);
	bool getBoolean(void);
	int getInt(void);
	JSONObject getJSONObject(void);
};

#endif /* SRC_RESPONSE_H_ */
