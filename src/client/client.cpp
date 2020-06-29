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
void analysisMenu();
void superUser();
void exportImportMenu(int userID);
bool testSession();
Session getSessionDb();

int userID = 1;
std::string userName = "- You are now in DEBUG:no-login mode";

bool login() {
	heading("Login Page");
	printLine();
	std::string login = "";
	std::string password = "";
	cout << "Please enter your login credentials: " << endl << endl;

	cout << "Login\t\t: ";
	getline(cin, login);

	cout << "Password\t: ";
	getline(cin, password);

	cout << endl << "Verifying your login credentials, please wait.";
	// Get salt
	std::string salt = "";
	try {
		Session sess = getSessionDb();

		auto myRows = sess.sql("SELECT salt FROM USER WHERE memberID=(SELECT memberID FROM MEMBER WHERE matrixNo=?)").bind(login).execute();

		if (myRows.count() != 1) {
			cout << "\n\nLogin error. Please try again." << endl;
			pause();
			return false;
		}
		else {
			// Write into salt variable
			std::stringstream ss1;

			auto myRow = myRows.fetchOne();

			myRow.get(0).print(ss1);
			salt = ss1.str();

		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "\rERROR: " << err << endl;
		pause();
		return false;
	}
	catch (...) {
		cout << "\rAn unknown error occured." << endl;
		pause();
		return false;
	}

	password = sha256(salt + password);

	std::string preparedStatement = "SELECT a.engName, b.userID FROM MEMBER a INNER JOIN USER b ON a.memberID=b.memberID WHERE ";
	preparedStatement += "a.matrixNo=? AND b.pw=?";

	try {

		Session sess = getSessionDb();

		auto myRows = sess.sql(preparedStatement).bind(login, password).execute();

		if (myRows.count() != 1) {
			cout << "\n\nLogin error. Please try again." << endl;
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

			cout << "\rWelcome " << userName << ". You are now logged in." << endl;

			pause();

			return true;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
		pause();
		return false;
	}
	catch (...) {
		cout << "An unknown error occured." << endl;
		pause();
		return false;
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
		heading("Startup diagnostics");
		printLine();
		cout << "Running startup diagnostic test...\nIf you see this message for an extended time there may be an issue.\nPress Ctrl + C to abort the application." << endl;
		if (!testSession()) {
			cout << "\nThere may be a connection problem. Open diagnostics?" << endl;
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
	*/
Relogin:
	while (!login()) {}

	unsigned int selection = 0;

	while (true) {
		json menuEntries = { "Member", "Activity", "Attendance", "User\n", "Analysis\n" ,"Diagnostics Information", "Data Administration" };

		heading("Welcome " + userName + ". Please select your scope of action.");
		printLine();

		cout << "Enter \"-1\" in any inputs (excluding yes/no prompts) to go back to sub-menu. \n\n";


		for (int i = 0; i < menuEntries.size(); i++) {
			cout << left << i + 1 << "\t" << returnString(menuEntries[i]) << endl;
		}
		cout << endl;
		cout << left << 10 << "\t" << "Logout" << endl;
		cout << left << -1 << "\t" << "Exit" << endl;


		try {
			selection = inputInt();
			if (selection > menuEntries.size() || selection < 0) {
				if (!(selection == 10 || selection == SUPERUSER_PASS_INT || selection == -1)) {
					throw "Error";
				}
			}

			if (selection == 1) {
				memberMenu();
			}
			else if (selection == 2) {
				activityMenu(userID);
			}
			else if (selection == 3) {
				attendanceMenu(userID);
			}
			else if (selection == 4) {
				userMenu();
			}
			else if (selection == 5) {
				analysisMenu();
			}
			else if (selection == 6) {
				additionalInformation();
			}
			else if (selection == 7) {
				exportImportMenu(userID);
			}
			else if (selection == SUPERUSER_PASS_INT) {
				superUser();
			}
			else if (selection == -1) {
				cout << "Thank you for using attendance management system by KwongTN." << endl;
				pause();
				exit(0);
			}
			else if (selection == 10) {
				goto Relogin;
			}
			else {
				cout << "Default pathway";
				throw "Invalid Selection";
			}


		}
		catch (const mysqlx::Error& err)
		{
			cout << "ERROR: " << err << endl;
			pause();
		}
		catch (...) {
			cout << "\nPlease input a valid selection. \n";
			pause();
		}

		cout << endl;
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
