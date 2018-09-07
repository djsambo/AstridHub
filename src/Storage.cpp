#include <FS.h>
#include <Arduino.h>
#include <Logbook.h>
#include <Storage.h>
#include <Utils.h>
#include <Error.h>

extern Utils utils;
extern Logbook logbook;

const String PATH_DBINFO = "/database/dbInfo.json";
const String PATH_DB = "/database/";
const int MAX_TABLE_NAME_SIZE = 21;
const String DB_EXT = ".db";

Storage::Storage() {
}

//------------------> Public Methods <------------------//

bool Storage::initialize() {
	bool sp = SPIFFS.begin();
	return sp;
}

Response Storage::listRecords(String table, JSONObject whereCondition) {
	if (table.length() < MAX_TABLE_NAME_SIZE) {
		std::list<JSONObject> responseData;

		if (!SPIFFS.exists(getTablePath(table))) {
			File newFile = SPIFFS.open(getTablePath(table), "w+");
			newFile.close();
		}

		File f = SPIFFS.open(getTablePath(table), "r");

		if (f) {
			while (f.available()) {
				JSONObject record(f.readStringUntil('\n'));

				if (whereCondition.size() > 0) {
					for (String key : whereCondition.getKeys()) {
						if (!record.containsKey(key))
							break;
						if (record.getString(key) != whereCondition.getString(key))
							break;
					}
				}

				responseData.push_back(record);
			}
			f.close();
		}

	} else {
		return Response(false, "The provided table name is to large, its must be less than 21 characters.");
	}
}

Response Storage::getRecord(String table, JSONObject whereCondition) {
	if (table.length() < MAX_TABLE_NAME_SIZE) {

		if (!SPIFFS.exists(getTablePath(table))) {
			File newFile = SPIFFS.open(getTablePath(table), "w+");
			newFile.close();
		}

		File f = SPIFFS.open(getTablePath(table), "r");

		if (f) {
			while (f.available()) {
				JSONObject record(f.readStringUntil('\n'));
				bool match = 0;

				if (whereCondition.size() > 0) {
					for (String key : whereCondition.getKeys()) {
						if (!record.containsKey(key))
							break;
						if (record.getString(key) == whereCondition.getString(key)) {
							match++;
							break;
						}
					}
				}

				if (match == whereCondition.size()) {
					return Response(record.toString());
					break;
				}
			}
			f.close();
		}
		return Response(false, "NOT_FOUND");
	} else {
		return Response(false, "The provided table name is to large, its must be less than 21 characters.");
	}
}

Response Storage::addRecord(String table, JSONObject& payload) {
	if (table.length() < MAX_TABLE_NAME_SIZE) {
		String tablePath = PATH_DB + table + DB_EXT;

		if (!SPIFFS.exists(tablePath)) {
			File newFile = SPIFFS.open(tablePath, "w+");
			newFile.close();
		}

		payload.put("id", utils.UUID());
		File f = SPIFFS.open(tablePath, "a");
		f.println(payload.toString());
		f.close();
		return Response(payload.toString());
	} else {
		return Response(false,"The provided table name is to large, its must be less than 21 characters.");
	}
}

Response Storage::updateRecord(String table, JSONObject whereCondition, JSONObject payload) {
	if (table.length() < MAX_TABLE_NAME_SIZE) {
		if (SPIFFS.exists(getTablePath(table))) {
			File f = SPIFFS.open(getTablePath(table), "r");
			std::list<JSONObject> bufferUpdate;

			if (f) {
				while (f.available()) {
					JSONObject record(f.readStringUntil('\n'));
					bool match = 0;

					if (whereCondition.size() > 0) {
						for (String key : whereCondition.getKeys()) {
							if (!record.containsKey(key))
								break;
							if (record.getString(key) == whereCondition.getString(key)) {
								match++;
								break;
							}
						}
					}

					if (match == whereCondition.size()) {
						for (String key : payload.getKeys()) {
							record.put(key, payload.getString(key));
						}
					}

					bufferUpdate.push_back(record);
				}
				f.close();
			}
			if (bufferUpdate.size() > 0) {
				File f = SPIFFS.open(getTablePath(table), "w");
				for (JSONObject r : bufferUpdate) {
					f.println(r.toString());
				}
				f.close();
			}
			return Response(true,"Record Updated.");
		} else {
			return Response(false,"The specified table not exist.");
		}
	} else {
		return Response(false,"The provided table name is to large, its must be less than 21 characters.");
	}
}

//------------------> Private Methods <------------------//

void Storage::listDirectory(String dirName) {
	Serial.print("Listing Directory: ");
	Serial.println(dirName);

	Dir dir = SPIFFS.openDir(dirName);
	while (dir.next()) {
		Serial.println("=====================================");
		Serial.print(dir.fileName() + " | ");
		File f = dir.openFile("r");
		Serial.println(f.size());
		Serial.println("=====================================");
	}
}

void Storage::formatDatabase() {
	if (SPIFFS.begin()) {
		if (SPIFFS.format()) {
			logbook.info("The database was formated correctly");
		} else {
			logbook.error("An error has occurred when database was formatting.");
		}
	}
}

String Storage::getTablePath(String tableName) {
	return PATH_DB + tableName + DB_EXT;
}
