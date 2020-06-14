#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
std::string columnNamesGen(json, std::string, std::string, std::string wrapper = "");
const std::string thisTableName = "USER";
const std::string innerJoin = "USER a INNER JOIN MEMBER b ON a.memberID=b.memberID";

json userDataStruct{
	{
		{"columnName", "userID"},
		{"altColumnName", "a.userID"},
		{"columnDescription", "User ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 10},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", true}
	},{
		{"columnName", "memberID"},
		{"altColumnName", "a.memberID"},
		{"columnDescription", "Member ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 10},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", true}
	},{
		{"columnName", "matrixNo"},
		{"altColumnName", "b.matrixNo"},
		{"columnDescription", "Matrix No."},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 15},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", false},
		{"correspondingTable", "MEMBER"},
		{"localJoin", "memberID"},
		{"externalJoin", "memberID"}
	},{
		{"columnName", "pw"},
		{"altColumnName", "a.pw"},
		{"columnDescription", "Password"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", false},
		{"outputSizing", 10},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true}
	},{
		{"columnName", "engName"},
		{"altColumnName", "b.engName"},
		{"columnDescription", "English Name"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 30},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"correspondingTable", "MEMBER"},
		{"localJoin", "memberID"},
		{"externalJoin", "memberID"}
	}

};

json userTempDataStore{};
json userTempDataStore2{};
// Create entry
void addEntry() {
	userTempDataStore.clear();

	heading("User Creation");
	printLine();
	cout << "Please input the following data to facilitate for user creation.\n* Indicates that entries with that value must be unique." << endl << endl;

	int tempCounter = 0;
	std::string matrixNo;
	// Getting Matrix No
	cout << left << std::setw(30) << "Matrix No." << "\t: ";
	getline(cin, matrixNo);
	for (int i = 0; i < userDataStruct.size(); i++) {
		std::string temp = "";
		if (userDataStruct[i]["input"]) {
			bool x = true;
			while (x) {
				std::string currString = returnString(userDataStruct[i]["columnDescription"]);
				if (userDataStruct[i]["isUnique"]) {
					currString += "*";
				}

				cout << left << std::setw(30) << currString << "\t: ";
				getline(cin, temp);
				if (userDataStruct[i]["compulsoryInput"] && temp == "") {
					cout << "Please input a value.";
				}
				else {
					if (temp != "") {
						userTempDataStore[tempCounter]["colName"] = userDataStruct[i]["columnName"];
						userTempDataStore[tempCounter]["colValue"] = temp;
						userTempDataStore[tempCounter]["getThis"] = true;

					}
					x = false;
				}

			}

			tempCounter++;

		}
	}


	std::string preparedStatement1 = "INSERT INTO " + thisTableName + " (memberID, ";
	preparedStatement1 += columnNamesGen(userTempDataStore, "getThis", "colName");
	preparedStatement1 += ") VALUES ((SELECT memberID FROM MEMBER WHERE matrixNo=?)";

	for (int i = 0; i < userTempDataStore.size(); i++) {
		preparedStatement1 += ", ?";
	}
	preparedStatement1 += ")";

	bool recover = true;
	while (recover) {
		try {
			Session sess = getSessionDb();

			auto mySess = sess.sql(preparedStatement1);

			mySess = mySess.bind(matrixNo);

			for (int i = 0; i < userTempDataStore.size(); i++) {
				mySess = mySess.bind(returnString(userTempDataStore[i]["colValue"]));
			}

			auto myRows = mySess.execute();

			if (myRows.getAffectedItemsCount() > 0) {
				cout << "\nRecord succesfully added" << endl;
				break;
			}
			else {
				throw;
			}

		}
		catch (const mysqlx::Error& err)
		{
			cout << "ERROR: " << err << endl;
			cout << "Do you want to try database action again?" << endl;
			recover = decider();
		}
		catch (...) {
			cout << "Unknown Error";
			cout << "Do you want to try database action again?" << endl;
			recover = decider();
		}

	}

	pause();
}
// Update entry
void updateEntry() {
	userTempDataStore.clear();
	system("cls");

	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("Update Member Entries.");
		printLine();
		cout << "Updating will be based on matrix no. Do you want to search user data?" << endl;

		if (!decider()) {
			break;
		}
		searchEntry();
	}


	std::string matrixNo;
	try {
		while (true) {
			system("cls");
			heading("Update Member Entries.");
			printLine();
			cout << "Please input member matrix no to update: ";
			getline(cin, matrixNo);

			std::string preparedStatement1 = "SELECT " + columnNamesGen(userDataStruct, "showDuringDeletion", "altColumnName") + " FROM " + innerJoin + " WHERE a.matrixNo=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(matrixNo).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				cout << "Are you sure you want to update the member with the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << left << std::setw(30) << returnString(userDataStruct[i]["columnDescription"]) << "\t: ";
						cout << row[i] << endl;
					}
					cout << endl;
				}

				if (decider()) {
					break;
				}
			}
			else {
				cout << "No member with matrix no. " << matrixNo << " found." << endl;
				cout << "Try again?" << endl;

				if (!decider()) {
					return;
				}
				pause();
			}
		}

		cout << endl;
	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	std::string preparedStatement2 = "UPDATE " + thisTableName + " SET ";
	int selection;
	int noOfChanges = 0;
	std::vector<int> selected;
	userTempDataStore2.clear();
	userTempDataStore.clear();

	// Selection to update.
	int counter = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["input"]) {
			userTempDataStore[counter]["colName"] = userDataStruct[i]["columnName"];
			userTempDataStore[counter]["colDesc"] = userDataStruct[i]["columnDescription"];
			userTempDataStore[counter]["notSelected"] = true;
			counter++;
		}
	}


	while (true) {
		heading("Updating member entry");
		printLine();

		while (true) {
		InvalidSelection:
			menuGen(userTempDataStore, "colDesc", "notSelected");
			selection = inputInt();

			// Check if selection was previously selected
			for (int i = 0; i < selected.size(); i++) {
				if (selection == selected[i]) {
					cout << "Please input a valid selection." << endl;
					pause();
					goto InvalidSelection;
				}
			}
			break;

		}

		std::string newData = "";
		cout << "Please input the new data for " << userTempDataStore[selection]["colDesc"] << endl;
		getline(cin, newData);

		if (noOfChanges > 0) {
			preparedStatement2 += ",";
		}

		preparedStatement2 += returnString(userTempDataStore[selection]["colName"]) + "=?";

		// Add changes into json
		userTempDataStore2[noOfChanges]["colDesc"] = userTempDataStore[selection]["colDesc"];
		userTempDataStore2[noOfChanges]["colData"] = newData;

		userTempDataStore[selection]["notSelected"] = false;
		selected.push_back(selection);

		noOfChanges++;

		if (noOfChanges >= userTempDataStore.size()) {
			break;
		}

		cout << "Do you want to add more data to update?" << endl;

		if (!decider()) {
			break;
		}
	}
	preparedStatement2 += " WHERE memberID=(SELECT memberID FROM MEMBER WHERE matrixNo=?)";

	cout << preparedStatement2 << endl;

	// Show current changes
	clearScreen();
	cout << "Current changes for member with matrix no " << matrixNo << " are :" << endl;
	for (int i = 0; i < userTempDataStore2.size(); i++) {
		cout << left << std::setw(20) << returnString(userTempDataStore2[i]["colDesc"]);
		cout << left << ": " << returnString(userTempDataStore2[i]["colData"]);
		cout << endl;
	}
	cout << endl;
	cout << "Are you sure you want to update the following data?" << endl;

	if (decider()) {
		Session sess = getSessionDb();
		auto mySess = sess.sql(preparedStatement2);

		for (int i = 0; i < userTempDataStore2.size(); i++) {
			mySess = mySess.bind(returnString(userTempDataStore2[i]["colData"]));
		}

		mySess = mySess.bind(matrixNo);

		auto myRows = mySess.execute();

		cout << endl;

		if (myRows.getAffectedItemsCount() > 0) {
			cout << "Update succesful." << endl;
		}
		else {
			cout << "There are probably some errors on the way." << endl;
		}
	}
	else {
		cout << "Decided to NOT update. ";
	}
	pause();
}

// Delete entry
void deleteEntry() {
	system("cls");

	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("Delete Member Entries.");
		printLine();
		cout << "Deleting will be based on matrix no. Do you want to search user data?" << endl;

		if (!decider()) {
			break;
		}
		searchEntry();
	}


	std::string matrixNo;
	try {
		do {
			system("cls");
			heading("Delete Member Entries.");
			printLine();
			cout << "Please input member matrix no to delete: ";
			getline(cin, matrixNo);

			userTempDataStore.clear();

			std::string preparedStatement1 = "SELECT " + columnNamesGen(userDataStruct, "showDuringDeletion", "altColumnName") + " FROM " + innerJoin + " WHERE b.matrixNo=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(matrixNo).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				cout << "Are you sure you want to delete the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << userDataStruct[i]["columnDescription"] << "\t: ";
						cout << row[i] << endl;
					}
					cout << endl;
				}
				break;
			}
			else {
				cout << "No member with matrix no. " << matrixNo << " found." << endl;
				cout << "Try again?" << endl;
			}
		} while (decider());

		cout << endl;

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	std::string preparedStatement2 = "DELETE FROM " + thisTableName + " WHERE memberID=(SELECT memberID FROM MEMBER WHERE matrixNo=?)";

	if (decider()) {
		Session sess = getSessionDb();
		auto myRows = sess.sql(preparedStatement2).bind(matrixNo).execute();

		cout << endl;

		if (myRows.getAffectedItemsCount() > 0) {
			cout << "Deletion succesful. " << myRows.getAffectedItemsCount() << " rows affected." << endl;
		}
		else {
			cout << "There are probably some errors on the way." << endl;
		}
	}
	else {
		cout << "Decided to NOT delete. ";
	}
	pause();
}



void userMenu() {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = { "Add User", "List Users", "Update User", "Delete User", "Search User" };

	clearScreen();

	// Show menu top
	heading("USER Management Menu");
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
		selection = inputInt(toggle);
		if (selection > menuEntries.size() || selection < 0) {
			if (selection != 10) {
				throw "Error";
			}
		}

		switch (selection)
		{
		case 1:
			addEntry();
			break;
		case 2:
			listEntries();
			break;
		case 3:
			updateEntry();
			break;
		case 4:
			deleteEntry();
			break;
		case 5:
			searchEntry();
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
		cout << "\nPlease input a valid selection. \n";
		pause();
		cin.clear();
	}

	cout << endl;
	toggle = !toggle;
	goto MenuStart;
}