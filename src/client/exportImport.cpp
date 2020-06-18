#include "utils.h"
#include <fstream>

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();

void exportFunc() {

	std::ofstream exportFile;
	std::string filePath = "";
	json exportDataStruct;
	int jsonSizer = 0;

	// Ask for output file path & check write access
	while (true) {
		heading("EXPORT");
		printLine();

		cout << "Please input the name (and path) of the file you would like to export to.\n> ";
		getline(cin, filePath);
		exportFile.open(filePath);

		if (exportFile.is_open()) {
			cout << "File succesfully opened." << endl;
			pause();
			break;
		}
		else {
			cout << "Unable to open file. Exit to menu?" << endl;
			if (decider()) {
				return;
			}
		}

	}

	// Select items to group, adding into vector to detect invalid selections
	std::vector<int> selected;
	int selection = 0;

	json selectionMenu = {
		{
			{"tableName", "Member"},
			{"notSelected", true}
		},{
			{"tableName", "User"},
			{"notSelected", true}
		},{
			{"tableName", "Activity"},
			{"notSelected", true}
		},{
			{"tableName", "Attendance"},
			{"notSelected", true}
		},{
			{"tableName", "Select All"},
			{"notSelected", true}
		}
	};

	while (true) {
		// Output selection menu
		while (true) {
			heading("EXPORT: Selecting tables to export");
			printLine();
			cout << "Exporting to \"" << filePath << "\"" << endl;
			cout << "Output json will be with respect to sequence." << endl << endl;

			menuGen(selectionMenu, "tableName", "notSelected");
			selection = inputInt();

			// Check if selection was previously selected
			if (selection == 4) {
				selected.push_back(0);
				selected.push_back(1);
				selected.push_back(2);
				selected.push_back(3);
			}
			if ((selection > selectionMenu.size() - 1) || vectorContains(selected, selection)) {
				cout << "Please input a valid selection." << endl;
				pause();
				continue;

			}
			else {
				break;

			}
		}
		selected.push_back(selection);
		selectionMenu[selection]["notSelected"] = false;

		if (selected.size() >= selectionMenu.size()) {
			break;
		}
		else {
			cout << "Do you want to add more tables to the export?" << endl;
			if (decider()) {
				continue;
			}
			else {
				break;
			}
		}
	}

	heading("Export operation");
	printLine();

	for (int i = 0; i < selected.size(); i++) {
		if (selectionMenu[selected[i]]["tableName"] == "Member") {
			cout << "\nMEMBER" << endl;
			cout << "|- Starting export from table \'Member\'" << endl;

			try {
				cout << "|- Querying database..." << endl;
				Session sess = getSessionDb();
				auto myRows = sess.sql("SELECT engName, matrixNo, hostel FROM MEMBER").execute();

				cout << "|- Assigning values..." << endl;
				exportDataStruct[jsonSizer]["type"] = "member";

				int rowCount = 0;
				int totalRowCount = myRows.count();
				for (Row row : myRows.fetchAll()) {
					std::stringstream ss1, ss2, ss3;

					row.get(0).print(ss1);
					row.get(1).print(ss2);
					row.get(2).print(ss3);

					exportDataStruct[jsonSizer]["values"][rowCount]["engName"] = ss1.str();
					exportDataStruct[jsonSizer]["values"][rowCount]["matrixNo"] = ss2.str();

					if (ss3.str() != "<null>") {
						exportDataStruct[jsonSizer]["values"][rowCount]["hostel"] = ss3.str();

					}

					rowCount++;
				}

				cout << "|- Exported " << rowCount << " of " << totalRowCount << " results from table \'Member\'." << endl;

				jsonSizer++;
			}
			catch (const mysqlx::Error& err)
			{
				cout << "ERROR: " << err << endl;
			}
			catch (...) {
				cout << "An unknown error occured." << endl;
			}
		}
		else if (selectionMenu[selected[i]]["tableName"] == "User") {
			cout << "\nUSER" << endl;
			cout << "|- Starting export from table \'User\'" << endl;

			try {
				cout << "|- Querying database..." << endl;
				Session sess = getSessionDb();
				auto myRows = sess.sql("SELECT matrixNo, pw FROM USER a INNER JOIN MEMBER b ON a.memberID=b.memberID").execute();

				cout << "|- Assigning values..." << endl;
				exportDataStruct[jsonSizer]["type"] = "user";

				int rowCount = 0;
				int totalRowCount = myRows.count();
				for (Row row : myRows.fetchAll()) {
					std::stringstream ss1, ss2;

					row.get(0).print(ss1);
					row.get(1).print(ss2);

					exportDataStruct[jsonSizer]["values"][rowCount]["matrixNo"] = ss1.str();
					exportDataStruct[jsonSizer]["values"][rowCount]["pw"] = ss2.str();

					rowCount++;
				}

				cout << "|- Exported " << rowCount << " of " << totalRowCount << " results from table \'User\'." << endl;

				jsonSizer++;
			}
			catch (const mysqlx::Error& err)
			{
				cout << "ERROR: " << err << endl;
			}
			catch (...) {
				cout << "An unknown error occured." << endl;
			}
		}
		else if (selectionMenu[selected[i]]["tableName"] == "Activity") {
			cout << "\nACTIVITY" << endl;
			cout << "|- Starting export from table \'Activity\'" << endl;

			try {
				cout << "|- Querying database..." << endl;
				Session sess = getSessionDb();
				auto myRows = sess.sql("SELECT activityID, activityName, activityLocation, activityDesc, concat(activityYear, \'-\', if(activityMonth<10, concat(\'0\', activityMonth), activityMonth), \'-\', if(activityDay<10, concat(\'0\', activityDay), activityDay), \'T\', if(activityHour<10, concat(\'0\', activityHour), activityHour), \':\', if(activityMinute<10, concat(\'0\', activityMinute), activityMinute), \'Z\') AS DateTime, activityYear, activityMonth, activityDay, activityHour, activityMinute FROM ACTIVITY;").execute();

				exportDataStruct[jsonSizer]["type"] = "activity";

				int rowCount = 0;
				int totalRowCount = myRows.count();
				cout << "|- Assigning values...";
				for (Row row : myRows.fetchAll()) {
					std::stringstream ss[10];

					for (int i = 0; i < 10; i++) {
						row.get(i).print(ss[i]);

					}

					exportDataStruct[jsonSizer]["values"][rowCount]["activityID"] = toInt(ss[0].str());
					exportDataStruct[jsonSizer]["values"][rowCount]["activityName"] = ss[1].str();
					exportDataStruct[jsonSizer]["values"][rowCount]["activityLocation"] = ss[2].str();
					if (ss[3].str() != "<null>") {
						exportDataStruct[jsonSizer]["values"][rowCount]["activityDesc"] = ss[3].str();
					}
					exportDataStruct[jsonSizer]["values"][rowCount]["activityDateTime"] = ss[4].str();
					exportDataStruct[jsonSizer]["values"][rowCount]["activityYear"] = toInt(ss[5].str());
					exportDataStruct[jsonSizer]["values"][rowCount]["activityMonth"] = toInt(ss[6].str());
					exportDataStruct[jsonSizer]["values"][rowCount]["activityDay"] = toInt(ss[7].str());
					exportDataStruct[jsonSizer]["values"][rowCount]["activityHour"] = toInt(ss[8].str());
					exportDataStruct[jsonSizer]["values"][rowCount]["activityMinute"] = toInt(ss[8].str());

					rowCount++;
				}

				cout << endl;
				cout << "|- Exported " << rowCount << " of " << totalRowCount << " results from table \'Activity\'." << endl;

				jsonSizer++;
			}
			catch (const mysqlx::Error& err)
			{
				cout << "ERROR: " << err << endl;
			}
			catch (...) {
				cout << "An unknown error occured." << endl;
			}
		}
		else if (selectionMenu[selected[i]]["tableName"] == "Attendance") {
			cout << "\nATTENDANCE" << endl;
			cout << "|- Starting export from table \'Attendance\'" << endl;

			try {
				cout << "|- Querying database - Level 1..." << endl;
				Session sess = getSessionDb();
				auto myRows = sess.sql("SELECT activityID FROM ATTENDANCE GROUP BY activityID").execute();

				exportDataStruct[jsonSizer]["type"] = "attendance";

				int rowCount = 0;
				int totalRowCount = 0;
				cout << "|- Assigning values - Level 1..." << endl;
				for (Row row : myRows.fetchAll()) {
					std::stringstream ss1, ss2;
					row.get(0).print(ss1);

					std::string activityID = ss1.str();

					exportDataStruct[jsonSizer]["values"][rowCount]["activityID"] = toInt(activityID);

					// Get activity name based on activity ID
					cout << "|- Querying database - Level 2-1..." << endl;
					auto myRows2 = sess.sql("SELECT activityName FROM ATTENDANCE a INNER JOIN ACTIVITY b ON a.activityID=b.activityID WHERE a.activityID=? GROUP BY a.activityID").bind(activityID).execute();
					myRows2.fetchOne().get(0).print(ss2);
					std::string activityName = ss2.str();
					exportDataStruct[jsonSizer]["values"][rowCount]["activityName"] = activityName;

					// Get activity name based on activity ID
					cout << "|- Querying database - Level 2-2..." << endl;
					auto myRows3 = sess.sql("SELECT matrixNo FROM ATTENDANCE a INNER JOIN MEMBER b ON a.memberID=b.memberID WHERE activityID=? GROUP BY b.matrixNo").bind(activityID).execute();

					int counter = 0;
					for (Row row3 : myRows3.fetchAll()) {
						std::stringstream ss3;
						row3.get(0).print(ss3);
						std::string matrixNo = ss3.str();
						exportDataStruct[jsonSizer]["values"][rowCount]["attendees"][counter] = matrixNo;

						counter++;
						totalRowCount++;
					}
					rowCount++;



				}

				cout << "|- Exported " << totalRowCount << " results from table \'Attendance\'." << endl;

				jsonSizer++;
			}
			catch (const mysqlx::Error& err)
			{
				cout << "ERROR: " << err << endl;
			}
			catch (...) {
				cout << "An unknown error occured." << endl;
			}
		}
	}
	cout << "\nWrite result" << endl;
	cout << "|- Data path: \'" << filePath << "\'" << endl;
	cout << "|- Writing results to file..." << endl;
	exportFile << exportDataStruct.dump(2) << endl;
	cout << "|- Write complete. Closing file.." << endl;
	exportFile.close();

	pause();
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