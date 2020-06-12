#include "utils.h"
#include "parameters.h"
#include <mysqlx/xdevapi.h>

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
 * @param {json} dbColumns - dbColumns in a specific JSON format
 * @param {std::string} determining - value determining whether to include the value in that index. Colapsible to bool.
 * @param {std::string} myOutput - output key
*/
std::string columnNamesGen(json dbColumns, std::string determining, std::string myOutput, std::string wrapper ) {
	std::string preparedStatement;
	unsigned short int loop = 0;
	for (int i = 0; i < dbColumns.size(); i++) {
		if (dbColumns[i][determining]) {
			if (loop > 0) {
				preparedStatement += ", ";

			}

			preparedStatement += wrapper;
			preparedStatement += dbColumns[i][myOutput];
			preparedStatement += wrapper;
			loop++;
		}
	}

	return preparedStatement;
}


/*
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
*/