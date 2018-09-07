/*
 * Error.h
 *
 *  Created on: Aug 25, 2018
 *      Author: dsambo
 */

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

#include <WString.h>
#include <exception>

class Error: public std::exception {
private:
	String message;
	String code;
public:
	explicit Error(String message);
	explicit Error(String code, String message);
	String getMessage(void);
	String getCode(void);
	virtual const char* what() const throw () {
		return message.c_str();
	}
};

#endif /* SRC_ERROR_H_ */
