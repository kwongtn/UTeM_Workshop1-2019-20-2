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