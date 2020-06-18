#include "utils.h"
#include <fstream>

void exportFunc() {

}

void importFunc() {

}

void exportImportMenu() {
	unsigned short int selection = 0;

	while (true) {
		json menuEntries = {
			"Export Entries",
			"Import Entries"
		};


		clearScreen();

		// Show menu top
		heading("Export Import Menu");
		printLine();

		// Show menu selection
		for (int i = 0; i < menuEntries.size(); i++) {
			cout << left << i + 1 << "\t" << returnString(menuEntries[i]) << endl;
		}
		cout << endl;
		cout << left << 10 << "\t" << "Back to Main Menu" << endl << endl;
		bool toggle = false;
		try {
			cout << "Please input your selection: " << endl;
			selection = inputInt();
			if (selection > menuEntries.size() || selection < 0) {
				if (selection != 10) {
					throw "Error";
				}
			}

			switch (selection)
			{
			case 1:
				exportFunc();
				break;
			case 2:
				importFunc();
				break;
			case 10:
				return;
				break;
			default:
				cout << "Default pathway";
				throw "Invalid Selection";
				break;
			}
		}
		catch (...) {
			cout << "\nMenu: Please input a valid selection. \n";
			pause();
		}

		cout << endl;
	}
}