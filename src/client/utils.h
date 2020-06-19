#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
#include <array>
#include <vector>
#include <sstream>
#include <windows.h>
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
		cout << character;
	}

	cout << "\n";
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

inline int menuGen(json rowNames) {
	int j = 0;
	for (int i = 0; i < rowNames.size(); i++) {
		cout << i << "\t" << returnString(rowNames[i]) << endl;
		j++;
	}
	cout << endl;
	return j;
}


inline int menuGen(json rowNames, std::string myOutput) {
	int j = 0;
	for (int i = 0; i < rowNames.size(); i++) {
		cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;
		j++;
	}
	cout << endl;
	return j;
}

inline int menuGen(json rowNames, std::string myOutput, std::string determiner) {
	int j = 0;
	for (int i = 0; i < rowNames.size(); i++) {
		if (rowNames[i][determiner]) {
			cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;
			j++;
		}
	}
	cout << endl;
	return j;
}


inline bool decider(std::string custString = "Your selection (y / n): ") {
	bool x = true;
	std::string selection;
	while (true) {
		cout << custString;
		try {
			getline(cin, selection);
			if (selection == "y" || selection == "Y") {
				x = true;
				break;
			}
			else if (selection == "n" || selection == "N") {
				x = false;
				break;
			}
			else {
				throw "Error";
			}
			if (cin.fail() || selection != "y" || selection != "Y" || selection != "n" || selection != "N") {
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
inline bool arrayContains(json myJSON, std::string element) {
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

// Whether a vector contains a value
template <typename T1>
inline bool vectorContains(std::vector<T1> myVector, T1 against) {
	try {
		if (myVector.size() == 0) {
			return false;
		}
		for (int i = 0; i < myVector.size(); i++) {
			if (myVector[i] == against) {
				return true;
			}
		}
		return false;

	}
	catch (...) {
		return false;
	}
}

inline int inputInt(bool prompter = true, bool forceInput = true) {
	std::string myString = "";
	int i;
	while (true) {
		cin.clear();
		if (prompter) {
			cout << "\n> ";
		}
		getline(cin, myString);

		if (myString == "" && !forceInput) {
			return -1000;
		}

		try
		{
			i = std::stoi(myString);
			break;
		}
		catch (std::invalid_argument const& e)
		{
			cout << "Bad input: std::invalid_argument thrown. Please re-input." << '\n';
			!prompter ? prompter = !prompter : prompter;
			continue;
		}
		catch (std::out_of_range const& e)
		{
			cout << "Integer overflow: std::out_of_range thrown. Please re-input." << '\n';
			!prompter ? prompter = !prompter : prompter;
			continue;
		}

	}

	return i;

}

inline int toInt(std::string myString) {
	try
	{
		int i = std::stoi(myString);
		return i;
	}
	catch (std::invalid_argument const& e)
	{
		cout << "Bad input: std::invalid_argument thrown." << '\n';
	}
	catch (std::out_of_range const& e)
	{
		cout << "Integer overflow: std::out_of_range thrown. Please re-input." << '\n';
	}
	return 0;
}