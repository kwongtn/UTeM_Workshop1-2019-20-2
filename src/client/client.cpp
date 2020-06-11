// client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "utils.h"


void mainMenu() {
	const int MENU_SIZE = 5;
	unsigned short int selection = 0;

MenuStart:
	std::string menuEntries[] = { "User", "Member", "Activity", "Attendance", "Additional Information" };

	system("cls");

	cout << "Welcome. Please select your scope of action." << endl;

	printLine();

	for (int i = 0; i < MENU_SIZE; i++) {
		cout << left << i + 1 << "\t" << menuEntries[i] << endl;
	}
	cout << left << 10 << "\t" << "Exit" << endl;

	try {
		cin >> selection;
		if (cin.fail() || selection > MENU_SIZE || selection < 0) {
			throw "Error";
		}

		switch (selection)
		{
		case 1:
			// TODO: User menu
			break;
		case 2:
			// TODO: Member menu
			break;
		case 3:
			// TODO: Activity Menu
			break;
		case 4:
			//TODO: Attendance Menu
			break;
		case 5:
			additionalInformation();
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
		cout << "Please input a valid selection. \n";
		cin.clear();
	}

	system("pause");
	goto MenuStart;
}

int main() {


	mainMenu();

	/*
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

	*/

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
