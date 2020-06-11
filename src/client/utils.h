#pragma once
#include <iostream>
#include <mysqlx/xdevapi.h>
#include <iomanip>
#include <cstring>

#include "parameters.h"

using ::std::cout;
using ::std::cin;
using ::std::left;
using ::std::endl;
using ::std::stoi;

void printLine(char character = '=', int length = 20) {
	for (int i = 0; i < length; i++) {
		std::cout << character;
	}

	std::cout << std::endl;
}

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

	cout << "===== DB Connection test =====" << endl;

	cout << "DB Address\t: " << DB_ADDRESS << ":" << DB_PORT << endl;
	cout << "Target Schema\t:" << SCHEMA << endl;

	// Database connection test
	try {
		using namespace ::mysqlx;

		Session sess(
			SessionOption::HOST, DB_ADDRESS,
			SessionOption::PORT, DB_PORT,
			SessionOption::USER, DB_LOGIN,
			SessionOption::PWD, DB_PASS
		);

		cout << "\nDatabase Connection success." << endl;

		// Access schema
		Schema db = sess.getSchema(SCHEMA);
		cout << "\nCompleted getting schema." << endl;

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}

}
