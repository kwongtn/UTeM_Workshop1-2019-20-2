#include "utils.h"

using namespace ::mysqlx;

bool testSession();
bool testDb(std::string);
Session getSessionDb();

void additionalInformation() {
	heading("Additional diagnostic information");
	printLine();

	cout << "Please contact your system administrator for special access codes if you really do need them." << endl << endl;

	// C++ Version
	cout << "===== C++ Version =====" << endl;
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
	else std::cout << "pre-standard C++\n";

	std::cout << "Using C++ version " << __cplusplus << std::endl;

	cout << "\n===== DB Connection test =====" << endl;

	cout << "DB Address\t: " << DB_ADDRESS << ":" << DB_PORT << endl;
	cout << "Target Schema\t: " << SCHEMA << endl;

	// Database test
	try {
		cout << endl;
		cout << "Testing database server connection." << "\r";

		if (testSession()) {
			cout << "> Database Server Connection success." << endl;
		}
		else {
			cout << "> Error in database server connection." << endl;
		}

		cout << endl;
		cout << "Testing database connection." << "\r";
		// Access schema
		if (testDb(SCHEMA)) {
			cout << "> Database Connection success." << endl;
		}
		else {
			cout << "> Error in database connection. Database probably having error." << endl;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}

	/*
	try {
		auto db = getSessionDb();

		auto myRows = db.sql("SELECT * FROM MEMBER WHERE engName like ?").bind("K%").execute();

		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << row[i] << "\t";
			}
			cout << endl;
		}
		
	}
	catch (const mysqlx::Error& err) {
		cout << "ERROR " << err << endl;
	}*/

	pause();
}
