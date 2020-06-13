#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
#include <array>
#include <mysqlx/xdevapi.h>
#include "../libs/json.hpp"

#include "parameters.h"

using ::std::cout;
using ::std::cin;
using ::std::left;
using ::std::endl;

using json = nlohmann::json;

inline void printLine(char character = '=', int length = 20) {
	for (int i = 0; i < length; i++) {
		std::cout << character;
	}

	std::cout << std::endl;
}

inline void pause() {
	cout << endl;
	system("pause");
}

inline void clearScreen() {
	system("cls");
}

inline void heading() {
	cout << "Club Attendance Management System" << endl << endl;
}

inline std::string returnString(json i) {
	return i;
}


inline void menuGen(json rowNames, std::string myOutput) {
	for (int i = 0; i < rowNames.size(); i++) {
		cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;
	}
}


inline bool decider() {
	bool x = true;
	char selection;
	while (true) {
		cout << "Your selection (y / n): ";
		try {
			cin >> selection;
			if (selection == 'y' || selection == 'Y') {
				x = true;
				break;
			}
			else if (selection == 'n' || selection == 'N') {
				x = false;
				break;
			}
			else {
				throw "Error";
			}
			if (cin.fail() || selection != 'y' || selection != 'Y' || selection != 'n' || selection != 'N') {
				throw "Error";
			}
		}
		catch (...) {
			cout << selection;
			cout << "Please enter a valid character." << endl;
			pause();
		}
	}
	return x;

}
