#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
#include <array>
#include <vector>
#include <sstream>
#include <mysqlx/xdevapi.h>
#include "../libs/json.hpp"

#include "parameters.h"

using ::std::cout;
using ::std::cin;
using ::std::left;
using ::std::endl;

using json = nlohmann::json;

inline void printLine(char character = '=', int length = 30) {
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

inline void heading(std::string additional = "") {
	system("cls");
	cout << "Club Attendance Management System" << endl << endl;

	if (additional != "") {
		cout << additional << endl;
	}
}

inline std::string returnString(json i) {
	return i;
}


inline void menuGen(json rowNames, std::string myOutput) {
	for (int i = 0; i < rowNames.size(); i++) {
		cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;
	}
	cout << endl;
}

inline void menuGen(json rowNames, std::string myOutput, std::string determiner) {
	for (int i = 0; i < rowNames.size(); i++) {
		if (rowNames[i][determiner]) {
			cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;

		}
	}
	cout << endl;
}


inline bool decider(std::string custString = "Your selection (y / n): ") {
	bool x = true;
	char selection;
	while (true) {
		cout << custString;
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
			cout << "Please enter a valid character." << endl;
			pause();
		}
	}
	return x;

}

// Whether an array of values contain a key
inline bool jsonContains(json myJSON, std::string element) {
	if (myJSON.size() == 0) {
		return false;
	}
	for (int i = 0; i < myJSON.size(); i++) {
		if (myJSON[i].contains(element)) {
			return true;
		}
	}

	return false;
}