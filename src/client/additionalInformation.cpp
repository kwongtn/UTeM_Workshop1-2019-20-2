#include "utils.h"

bool testSession();
bool testDb(std::string);
void additionalInformation() {
	system("cls");

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

		if (testSession()) {
			cout << "\nDatabase Server Connection success." << endl;
		}
		else {
			cout << "\nError in database server connection." << endl;
		}

		// Access schema
		if (testDb(SCHEMA)) {
			cout << "\nDatabase Connection success." << endl;
		}
		else {
			cout << "\nError in database connection. Database name probably having error." << endl;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}

}
