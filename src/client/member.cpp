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
		{"searchable", false}
	},
	{
		{"columnName", "engName"},
		{"columnDescription", "English Name"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true}
	},
	{
		{"columnName", "matrixNo"},
		{"columnDescription", "Matrix No"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true}
	},
	{
		{"columnName", "email"},
		{"columnDescription", "E-Mail"},
		{"input", true},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false}
	},
	{
		{"columnName", "hostel"},
		{"columnDescription", "Hostel"},
		{"input", true},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true}
	},
	{
		{"columnName", "signupTime"},
		{"columnDescription", "Signup Time"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false}
	},
	{
		{"columnName", "updateTime"},
		{"columnDescription", "Update Time"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false}
	}
};

json memberTempDataStore{};

// Search entry
void searchEntry() {
	system("cls");
	memberTempDataStore.clear();
	cin.ignore();

	// Copies searchable items to memberTempDataStore
	int tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["searchable"]) {
			memberTempDataStore[tempCounter]["colName"] = memberDataStruct[i]["columnName"];
			memberTempDataStore[tempCounter]["colDesc"] = memberDataStruct[i]["columnDescription"];

			tempCounter++;
		}
	}

	std::string preparedStatement = "SELECT " + columnNamesGen(memberDataStruct, "selected", "columnName") + " FROM " + thisTableName + " WHERE ";

	bool y = true;
	int counter = 0;
	while (y) {

		menuGen(memberTempDataStore, "colDesc");
		cout << memberTempDataStore.flatten() << endl;

		bool x = true;
		int selection;
		while (x) {
			cout << "Please select the column you would like to search by: ";
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
				system("pause");
			}

		}

		cout << "Selected " << memberTempDataStore[selection]["colDesc"] << endl;

		// To get search criteria
		cout << "Please input the search criteria. ";

		std::string criteria = "";
		cin.ignore();
		std::getline(cin, criteria);

		cout << "Criteria: SELECT " << memberTempDataStore[selection]["colDesc"] << " WHERE " << criteria << endl;

		if (counter > 0) {
			preparedStatement += " AND ";
		}
		preparedStatement += returnString(memberTempDataStore[selection]["colName"]) + " like \'" + criteria + "\'";

		counter++;

		cout << "Would you like to add criteria? " << endl;
		y = decider();
	}

	cout << "\nCurrent search statement:" << endl;
	cout << preparedStatement << endl;

	try {
		Session sess = getSessionDb();

		auto myRows = sess.sql(preparedStatement).execute();

		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(50) << row[i] << "\t";
			}
			cout << endl;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	system("pause");



}

// Create entry
void addEntry() {
	memberTempDataStore.clear();
	cin.ignore();

	cout << "Please input the following data to facilitate for member creation." << endl;

	int tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {

		std::string temp = "";

		if (memberDataStruct[i]["input"]) {
			bool x = true;
			while (x) {
				cout << returnString(memberDataStruct[i]["columnDescription"]) << "\t: ";
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

	try {
		Session sess = getSessionDb();

		auto myRows = sess.sql(preparedStatement).execute();

		if (myRows.getAffectedItemsCount() > 0) {
			cout << "Record succesfully added" << endl;
		}
		else {
			throw;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	system("pause");
}

// List entry
void listEntries() {

	try {
		Session sess = getSessionDb();

		std::string selection = columnNamesGen(memberDataStruct, "selected", "columnName");

		auto myRows = sess.sql("SELECT " + selection + " FROM " + thisTableName)
			.execute();

		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(50) << row[i] << "\t";
			}
			cout << endl;
		}

	}
	catch (const mysqlx::Error& err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (...) {
		cout << "Unknown Error";
	}

	system("pause");
}

// Update entry


// Delete entry




void memberMenu() {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = { "Add Member", "List Members", "Update Member", "Delete Member", "Search Member" };

	clearScreen();

	heading();
	cout << "MEMBER" << endl;

	printLine();


	for (int i = 0; i < menuEntries.size(); i++) {
		cout << left << i + 1 << "\t" << returnString(menuEntries[i]) << endl;
	}
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

			break;
		case 4:

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
		system("pause");
		cin.clear();
	}

	cout << endl;
	goto MenuStart;
}