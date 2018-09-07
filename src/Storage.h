#ifndef Storage_h
#define Storage_h

#include <JSONObject.h>
#include <WString.h>
#include <list>
#include <Response.h>

class Storage {
public:
	Storage();
	bool initialize();
	Response getRecord(String table, JSONObject whereCondition);
	Response listRecords(String table, JSONObject whereCondition);
	Response addRecord(String table, JSONObject& payload);
	Response updateRecord(String table, JSONObject whereCondition,
			JSONObject payload);
private:
	void listDirectory(String dirName);
	void formatDatabase();
	String getTablePath(String tableName);
};

#endif
