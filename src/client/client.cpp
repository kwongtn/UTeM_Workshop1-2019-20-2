// client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "utils.h"
#include "sha256.h"
// #define _WIN32_WINNT 0x0500
// #include <windows.h>

using namespace ::mysqlx;

// Function declaration from other files
void userMenu();
void memberMenu();
void additionalInformation();
void activityMenu(int userID);
void attendanceMenu(int userID);
void superUser();
bool testSession();
Session getSessionDb();

int userID;
std::string userName;

void mainMenu() {
	unsigned int selection = 0;

MenuStart:
	json menuEntries = { "Member", "Activity", "Attendance", "User", "Additional Information" };

	clearScreen();

	heading();
	cout << "Welcome. Please select your scope of action." << endl;

	printLine();


	for (int i = 0; i < menuEntries.size(); i++) {
		cout << left << i + 1 << "\t" << returnString(menuEntries[i]) << endl;
	}
	cout << endl;
	cout << left << 10 << "\t" << "Exit" << endl;


	try {
		selection = inputInt();
		if (selection > menuEntries.size() || selection < 0) {
			if (!(selection == 10 || selection == 1783174)) {
				throw "Error";
			}
		}

		switch (selection)
		{
		case 1:
			memberMenu();
			break;
		case 2:
			activityMenu(userID);
			break;
		case 3:
			attendanceMenu(userID);
			break;
		case 4:
			userMenu();
			break;
		case 5:
			additionalInformation();
			break;
		case 1783174:
			superUser();
			break;
		case 10:
			exit(0);
			break;
		default:
			cout << "Default pathway";
			throw "Invalid Selection";
			break;
		}
	}
	catch (...) {
		cout << "\nPlease input a valid selection. \n";
		pause();
	}

	cout << endl;
	goto MenuStart;
}

bool login() {
	system("cls");
	std::string login = "";
	std::string password = "";
	cout << "Please enter your login credentials: " << endl << endl;

	cout << "Login\t\t: ";
	getline(cin, login);

	cout << "Password\t: ";
	getline(cin, password);


	std::string preparedStatement = "";
	preparedStatement += "SELECT a.engName, b.userID FROM MEMBER a INNER JOIN USER b ON a.memberID=b.memberID WHERE ";
	preparedStatement += "a.matrixNo=? AND b.pw=?";

	cout << "Verifying your login credentials, please wait." << endl;
	try {

		Session sess = getSessionDb();

		auto myRows = sess.sql(preparedStatement).bind(login, sha256(password)).execute();

		if (myRows.count() != 1) {
			cout << "Login error. Please try again." << endl;
			system("pause");
			return false;
		}
		else {
			// Write into username and userID
			std::stringstream ss1, ss2;

			auto myRow = myRows.fetchOne();

			myRow.get(0).print(ss1);
			userName = ss1.str();

			myRow.get(1).print(ss2);
			userID = std::stoi(ss2.str());

			cout << endl;
			cout << "Welcome " << userName << ". You are now logged in." << endl;

			pause();

			return true;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "An unknown error occured." << endl;
	}
	pause();
	return false;
}

int main() {
	/*
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 5000, 500, TRUE); // 800 width, 100 height
	*/

	while (true) {
		if (!testSession()) {
			cout << "There may be a connection problem. Open diagnostics?" << endl;
			if (decider()) {
				additionalInformation();
			}
		}
		else {
			break;
		}

	}

	/*
	// Makes window full screen
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	while (!login()) {}
	*/

	mainMenu();
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
