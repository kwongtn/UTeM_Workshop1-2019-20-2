#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
std::string columnNamesGen(json, std::string, std::string, std::string wrapper = "");
const std::string thisTableName = "MEMBER";

// Struct Definition for member object type
struct MEMBER {
	int memberID; // Primary Key
	std::string engName;
	std::string matrixNo;
	std::string icNo;
	std::string email;
	std::string phoneNo;
	std::string facebookID;
	std::string hostel;
};

json memberDataStruct{
	{
		{"columnName", "memberID"},
		{"columnDescription", "Member ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 30},
		{"updatable", false}
	},
	{
		{"columnName", "engName"},
		{"columnDescription", "English Name"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 30},
		{"updatable", true}
	},
	{
		{"columnName", "matrixNo"},
		{"columnDescription", "Matrix No"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 15},
		{"updatable", true}
	},/*
	{
		{"columnName", "email"},
		{"columnDescription", "E-Mail"},
		{"input", true},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 30},
		{"updatable", true}
	},*/
	{
		{"columnName", "hostel"},
		{"columnDescription", "Hostel"},
		{"input", true},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 10},
		{"updatable", true}
	},
	{
		{"columnName", "signupTime"},
		{"columnDescription", "Signup Time"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", false},
		{"outputSizing", 30},
		{"updatable", false}
	},
	{
		{"columnName", "updateTime"},
		{"columnDescription", "Update Time"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", false},
		{"outputSizing", 30},
		{"updatable", false}
	}
};

json memberTempDataStore{};
json memberTempDataStore2{};

// Search entry
void searchEntry() {
	system("cls");
	memberTempDataStore.clear();
	cin.ignore(1000, '\n');

	heading("Searching Member Entries.");
	printLine();

	// Copies searchable items to memberTempDataStore
	int tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["searchable"]) {
			memberTempDataStore[tempCounter]["colName"] = memberDataStruct[i]["columnName"];
			memberTempDataStore[tempCounter]["colDesc"] = memberDataStruct[i]["columnDescription"];
			memberTempDataStore[tempCounter]["outputSizing"] = memberDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	std::string preparedStatement = "SELECT " + columnNamesGen(memberDataStruct, "selected", "columnName") + " FROM " + thisTableName + " WHERE ";

	int counter = 0;
	std::string criteriaStringUser = "SELECT WHERE ";
	std::string criteriaStringSys = "";
	do {
		if (counter > 0) {
			cout << "Would you like an \'OR\' join towards the previous criteria? Default: \'AND\' join" << endl;
			if (decider()) {
				criteriaStringSys += " OR ";
				criteriaStringUser += " OR ";
			}
			else {
				criteriaStringSys += " AND ";
				criteriaStringUser += " AND ";
			}
		}

		menuGen(memberTempDataStore, "colDesc");

		bool x = true;
		int selection;
		while (x) {
			cout << "\nPlease select the column you would like to search by: ";
			try {

				if (!(cin >> selection) || selection > tempCounter || selection < 0) {
					throw "Error";
				}
				else {
					x = false;
				}
			}
			catch (...) {
				cout << "Please input a valid selection." << endl;
				pause();
			}

		}

		cout << "Selected " << memberTempDataStore[selection]["colDesc"] << endl;

		// To get search criteria
		cout << "Please input the search criteria. You may use SQL-based wildcards like \"%\"\n>";

		std::string criteria = "";
		cin.ignore(1000, '\n');
		std::getline(cin, criteria);

		criteriaStringUser += memberTempDataStore[selection]["colDesc"];
		criteriaStringUser += " is \"" + criteria + "\" \n";

		cout << "Criteria: SELECT WHERE " << criteriaStringUser;


		criteriaStringSys += returnString(memberTempDataStore[selection]["colName"]) + " like \'" + criteria + "\'";

		counter++;

		cout << "Would you like to add criteria? " << endl;

	} while (decider());

	cout << "\nCurrent search statement: " << endl;
	cout << criteriaStringUser << endl;

	preparedStatement += criteriaStringSys;

	try {
		Session sess = getSessionDb();

		auto myRows = sess.sql(preparedStatement).execute();

		int rowCount = 0;
		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(memberTempDataStore[i]["outputSizing"]) << row[i] << "\t";
			}
			cout << endl;

			rowCount++;
		}

		cout << endl;

		cout << "Returned " << rowCount << " results." << endl;
	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	pause();



}

// Create entry
void addEntry() {
	memberTempDataStore.clear();
	cin.ignore(1000, '\n');

	heading("Member Creation");
	printLine();
	cout << "Please input the following data to facilitate for member creation." << endl;

	int tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {

		std::string temp = "";

		if (memberDataStruct[i]["input"]) {
			bool x = true;
			while (x) {
				cout << returnString(memberDataStruct[i]["columnDescription"]) << "\t: ";
				cin.ignore(1000, '\n');
				std::getline(cin, temp);
				if (memberDataStruct[i]["compulsoryInput"] && temp == "") {
					cout << "Please input a value.";
				}
				else {
					if (temp != "") {
						memberTempDataStore[tempCounter]["colName"] = memberDataStruct[i]["columnName"];
						memberTempDataStore[tempCounter]["colValue"] = temp;
						memberTempDataStore[tempCounter]["getThis"] = true;

					}
					x = false;
				}

			}

			tempCounter++;

		}
	}


	std::string preparedStatement = "INSERT INTO " + thisTableName + " (";
	preparedStatement += columnNamesGen(memberTempDataStore, "getThis", "colName");
	preparedStatement += ") VALUES (";
	preparedStatement += columnNamesGen(memberTempDataStore, "getThis", "colValue", "\'");
	preparedStatement += ")";

	bool recover = true;
	while (recover) {
		try {
			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement).execute();
			
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
			cout << "Do you want to try again?" << endl;
			recover = decider();
		}
		catch (...) {
			cout << "Unknown Error";
			cout << "Do you want to try again?" << endl;
			recover = decider();
		}

	}

	pause();
}

// List entry
void listEntries() {
	heading("Listing Member entries.");
	printLine();

	// Print table headings
	int lineSize = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["searchable"]) {
		cout << left << std::setw(memberDataStruct[i]["outputSizing"]) << returnString(memberDataStruct[i]["columnDescription"]);
		lineSize += memberDataStruct[i]["outputSizing"];

		}
	}

	printLine(lineSize);

	// Print table content
	try {
		Session sess = getSessionDb();

		std::string selection = columnNamesGen(memberDataStruct, "selected", "columnName");

		auto myRows = sess.sql("SELECT " + selection + " FROM " + thisTableName)
			.execute();

		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(memberDataStruct[i]["outputSizing"]) << row[i] << "\t";
			}
			cout << endl;
		}

		cout << endl;

		cout << "Returned " << myRows.count() << " results." << endl;

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	cout << endl;
	pause();
}

// Update entry
void updateEntry() {
	memberTempDataStore.clear();
	cin.ignore(1000, '\n');
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
			cin.ignore(1000, '\n');
			getline(cin, matrixNo);

			std::string preparedStatement1 = "SELECT " + columnNamesGen(memberDataStruct, "showDuringDeletion", "columnName") + " FROM " + thisTableName + " WHERE matrixNo=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(matrixNo).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				cout << "Are you sure you want to update the member with the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << left << std::setw(30) << returnString(memberDataStruct[i]["columnDescription"]) << "\t: ";
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
	memberTempDataStore2.clear();
	memberTempDataStore.clear();

	// Selection to update.
	int counter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["input"]) {
			memberTempDataStore[counter]["colName"] = memberDataStruct[i]["columnName"];
			memberTempDataStore[counter]["colDesc"] = memberDataStruct[i]["columnDescription"];
			memberTempDataStore[counter]["notSelected"] = true;
			counter++;
		}
	}

	while (true) {
		heading("Updating member entry");
		printLine();

		while (true) {
		InvalidSelection:
			if (noOfChanges == memberTempDataStore.size()) {
				break;
			}

			menuGen(memberTempDataStore, "colDesc", "notSelected");
			if (noOfChanges > 0) {
				cin.ignore();

			}
			cin >> selection;

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
		cout << "Please input the new data for " << memberTempDataStore[selection]["colDesc"] << endl;
		cin.ignore();
		getline(cin, newData);

		if (noOfChanges > 0) {
			preparedStatement2 += ",";
		}

		preparedStatement2 += returnString(memberTempDataStore[selection]["colName"]) + "=\'" + newData + "\' ";

		// Add changes into json
		memberTempDataStore2[noOfChanges]["colDesc"] = memberTempDataStore[selection]["colDesc"];
		memberTempDataStore2[noOfChanges]["colData"] = newData;

		memberTempDataStore[selection]["notSelected"] = false;
		selected.push_back(selection);

		noOfChanges++;

		cout << "Do you want to add more data to update?" << endl;

		if (!decider()) {
			break;
		}
	}
	preparedStatement2 += " WHERE matrixNo=\'" + matrixNo + "\'";

	// Show current changes
	clearScreen();
	cout << "Current changes for member with matrix no " << matrixNo << " are :" << endl;
	for (int i = 0; i < memberTempDataStore2.size(); i++) {
		cout << left << std::setw(20) << returnString(memberTempDataStore2[i]["colDesc"]);
		cout << left << ": " << returnString(memberTempDataStore2[i]["colData"]);
		cout << endl;
	}
	cout << endl;
	cout << "Are you sure you want to update the following data?" << endl;

	if (decider()) {
		Session sess = getSessionDb();
		auto myRows = sess.sql(preparedStatement2).execute();

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
	cin.ignore();
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
			cin.ignore();
			getline(cin, matrixNo);

			memberTempDataStore.clear();

			std::string preparedStatement1 = "SELECT " + columnNamesGen(memberDataStruct, "showDuringDeletion", "columnName") + " FROM " + thisTableName + " WHERE matrixNo=\'" + matrixNo + "\'";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				cout << "Are you sure you want to delete the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << memberDataStruct[i]["columnDescription"] << "\t: ";
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

	std::string preparedStatement2 = "DELETE FROM " + thisTableName + " WHERE matrixNo=\'" + matrixNo + "\'";

	if (decider()) {
		Session sess = getSessionDb();
		cout << preparedStatement2 << endl;
		auto myRows = sess.sql(preparedStatement2).execute();

		cout << endl;

		if (myRows.getAffectedItemsCount() > 0) {
			cout << "Deletion succesful." << endl;
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



void memberMenu() {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = { "Add Member", "List Members", "Update Member", "Delete Member", "Search Member" };

	clearScreen();

	// Show menu top
	heading("MEMBER Management Menu");
	printLine();

	// Show menu selection
	for (int i = 0; i < menuEntries.size(); i++) {
		cout << left << i + 1 << "\t" << returnString(menuEntries[i]) << endl;
	}
	cout << endl;
	cout << left << 10 << "\t" << "Back to Main Menu" << endl << endl;


	try {
		cin >> selection;
		if (cin.fail() || selection > menuEntries.size() || selection < 0) {
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
	goto MenuStart;
}