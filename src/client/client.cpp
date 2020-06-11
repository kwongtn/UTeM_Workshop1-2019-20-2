// client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <mysqlx/xdevapi.h>

using ::std::cout;
using ::std::endl;

const std::string DB_ADDRESS = "127.0.0.1";
const int DB_PORT = 8689;
const std::string DB_LOGIN = "root";
const std::string DB_PASS = "password";
const std::string SCHEMA = "ATT_MGMT";

int main() {
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
	else std::cout << "pre-standard C++\n";

	std::cout << __cplusplus << std::endl;

	try {
		using namespace ::mysqlx;

		Session sess(
			SessionOption::HOST, DB_ADDRESS,
			SessionOption::PORT, DB_PORT,
			SessionOption::USER, DB_LOGIN,
			SessionOption::PWD, DB_PASS
		);

		cout << "Connection success!" << endl;

		// Access schema
		Schema db = sess.getSchema(SCHEMA);

		cout << "Completed getting schema." << endl;

		// Access table
		Table tb = db.getTable("MEMBER");

		cout << "Completed getting table." << endl;

		RowResult result = tb.select("memberID", "engName").execute();

		cout << "Completed selecting table columns." << endl;

		for (Row row : result.fetchAll()) {

			for (int i = 0; i < row.colCount(); i++) {
				cout << row[i] << "\t";
			}
			cout << endl;
		}

		cout << "\nComplete output." << endl;
	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
