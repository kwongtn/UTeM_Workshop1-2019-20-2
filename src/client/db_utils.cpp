#include <mysqlx/xdevapi.h>
#include "parameters.h"
#include "utils.h"

using namespace ::mysqlx;

Session getSession() {
	Session sess(
		SessionOption::HOST, DB_ADDRESS,
		SessionOption::PORT, DB_PORT,
		SessionOption::USER, DB_LOGIN,
		SessionOption::PWD, DB_PASS
	);

	return sess;
}

bool testSession() {
	try {
		getSession();
		return true;
	}
	catch (...) {
		return false;
	}
}

Session getSessionDb() {
	Session sess(
		SessionOption::HOST, DB_ADDRESS,
		SessionOption::PORT, DB_PORT,
		SessionOption::USER, DB_LOGIN,
		SessionOption::PWD, DB_PASS
	);

	sess.sql("USE " + SCHEMA).execute();

	return sess;
}


Schema getDb(std::string tableName = SCHEMA) {
	Session sess = getSession();

	Schema db = sess.getSchema(tableName);

	return db;
}

bool testDb(std::string tableName = SCHEMA) {
	try {
		getDb(tableName);
		return true;
	}
	catch (...) {
		return false;
	}
}

Table getTable(std::string tableName) {

	Schema db = getDb();

	Table tb = db.getTable(tableName);

	return tb;

}

/**
 *@param {json} dbColumns - dbColumns in a specific JSON format
*/
std::string columnNamesGen(json dbColumns) {
	std::string preparedStatement;
	unsigned short int loop = 0;
	for (int i = 0; i < dbColumns.size(); i++) {
		if (dbColumns[i]["selected"]) {
			if (loop > 0) {
				preparedStatement += ", ";

			}

			preparedStatement += dbColumns[i]["columnName"];
			loop++;
		}
	}

	return preparedStatement;
}


bool decider() {
	bool k = true;
	char selection;
	while (k) {
		cout << "Your selection (y / n): ";
		try {
			cin >> selection;
			if (cin.fail() || selection != 'y' || selection != 'Y' || selection != 'n' || selection != 'N') {
				throw;
			}
			else if (selection == 'y' || selection == 'Y') {
				return true;
			}
			else if (selection == 'n' || selection == 'N') {
				return false;
			}
			else {
				throw;
			}
		}
		catch (...) {
			cout << "Please enter a valid character." << endl;
			pause();
		}
	}

}