#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
std::string columnNamesGen(json, std::string, std::string, std::string wrapper = "");
const std::string thisTableName = "MEMBER";

// 
json memberDataStruct{
	{
		{"columnName", "memberID"},
		{"columnDescription", "Member ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 10},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", true},
		{"orderable", true}
	},
	{
		{"columnName", "engName"},
		{"columnDescription", "English Name"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 50},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true}
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
		{"updatable", true},
		{"isUnique", true},
		{"inThisTable", true},
		{"orderable", true}
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
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true}
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
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true}
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
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true}
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
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true}
	}
};

json memberTempDataStore{};
json memberTempDataStore2{};
json memberTempDataStore3{};

// Search entry
void memberSearchEntry() {
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

	// Copies orderable items to memberTempDataStore2
	tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["orderable"]) {
			memberTempDataStore2[tempCounter]["colName"] = memberDataStruct[i]["columnName"];
			memberTempDataStore2[tempCounter]["colDesc"] = memberDataStruct[i]["columnDescription"];
			memberTempDataStore2[tempCounter]["outputSizing"] = memberDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	// Copies listable items to memberTempDataStore3
	tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["selected"]) {
			memberTempDataStore3[tempCounter]["colName"] = memberDataStruct[i]["columnName"];
			memberTempDataStore3[tempCounter]["colDesc"] = memberDataStruct[i]["columnDescription"];
			memberTempDataStore3[tempCounter]["outputSizing"] = memberDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	std::string preparedStatement = "SELECT " + columnNamesGen(memberDataStruct, "selected", "columnName") + " FROM " + thisTableName + " WHERE ";

	int counter = 0;
	std::string criteriaStringUser = "Criteria: SELECT WHERE ";
	std::string criteriaStringSys = "";
	std::vector<std::string> criterias;

	do {
		heading("Searching Member Entries.");
		printLine();
		if (counter > 0) {
			cout << "\nCurrent " << criteriaStringUser << endl;
			cout << "\nWould you like an \'OR\' join towards the previous criteria? Default: \'AND\' join" << endl;
			if (decider()) {
				criteriaStringSys += " OR ";
				criteriaStringUser += " OR ";
			}
			else {
				criteriaStringSys += " AND ";
				criteriaStringUser += " AND ";
			}
		}

		heading("Searching Member Entries.");
		printLine();
		menuGen(memberTempDataStore, "colDesc");

		if (counter > 0) {
			cout << "\nCurrent " << criteriaStringUser << endl;

		}

		int selection;
		while (true) {
			cout << "\nPlease select the column you would like to search by: ";
			try {
				selection = inputInt();
				if (selection > memberTempDataStore.size() || selection < 0) {
					throw "Error";
				}
				else {
					break;
				}
			}
			catch (...) {
				cout << "Please input a valid selection." << endl;
				pause();
			}

		}

		// Search criteria input
		heading("MEMBER: Search Criteria Creation");
		printLine();
		if (counter > 0) {
			cout << "\nCurrent " << criteriaStringUser << endl << endl;

		}
		cout << "Selected " << memberTempDataStore[selection]["colDesc"] << endl;

		// To get search criteria
		cout << "Please input the search criteria. You may use SQL-based wildcards like \"%\"\n\n> ";

		std::string criteria = "";
		std::getline(cin, criteria);

		criterias.push_back(criteria);
		criteriaStringUser += memberTempDataStore[selection]["colDesc"];
		criteriaStringUser += " is \"" + criteria + "\" \n";

		cout << "\n\n" << criteriaStringUser;


		criteriaStringSys += returnString(memberTempDataStore[selection]["colName"]) + " like ?";

		counter++;

		cout << "\nWould you like to add criteria? " << endl;

	} while (decider());


	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("Search Result");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(memberTempDataStore2, "colDesc");
		selection = inputInt();
		if (selection < memberTempDataStore2.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	heading("Search Result");
	printLine();
	cout << "Search statement " << criteriaStringUser << endl;

	preparedStatement += criteriaStringSys + " ORDER BY " + returnString(memberTempDataStore2[selection]["colName"]);


	// Print table headings
	int lineSize = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["selected"]) {
			cout << left << std::setw(memberDataStruct[i]["outputSizing"]) << returnString(memberDataStruct[i]["columnDescription"]);

			lineSize += memberDataStruct[i]["outputSizing"];

		}
	}

	cout << endl;

	printLine('=', lineSize);


	try {
		Session sess = getSessionDb();

		auto mySess = sess.sql(preparedStatement);
		for (int i = 0; i < criterias.size(); i++) {
			mySess.bind(criterias[i]);
		}

		auto myRows = mySess.execute();

		// Print table content
		int rowCount = 0;
		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(memberTempDataStore3[i]["outputSizing"]) << row[i];
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
void memberAddEntry() {
	heading("Member Creation");
	printLine();
	cout << "Please input the following data to facilitate for member creation.\n* Indicates that entries with that value must be unique." << endl << endl;

	int tempCounter = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {

		std::string temp = "";

		if (memberDataStruct[i]["input"]) {
			bool x = true;
			while (x) {
				std::string currString = returnString(memberDataStruct[i]["columnDescription"]);
				if (memberDataStruct[i]["isUnique"]) {
					currString += "*";
				}

				cout << left << std::setw(30) << currString << "\t: ";
				getline(cin, temp);
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
	preparedStatement += ") VALUES (?";

	for (int i = 1; i < memberTempDataStore.size(); i++) {
		preparedStatement += ", ?";
	}
	preparedStatement += ")";

	bool recover = true;
	while (recover) {
		try {
			Session sess = getSessionDb();

			auto mySess = sess.sql(preparedStatement);

			for (int i = 0; i < memberTempDataStore.size(); i++) {
				mySess = mySess.bind(returnString(memberTempDataStore[i]["colValue"]));
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

// List entry
void memberListEntries() {
	// Copy relavant rows to tempDataStore
	int menuSize = 0;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["orderable"]) {
			memberTempDataStore[menuSize]["colDesc"] = memberDataStruct[i]["columnDescription"];
			memberTempDataStore[menuSize]["colName"] = memberDataStruct[i]["columnName"];
			memberTempDataStore[menuSize]["outputSizing"] = memberDataStruct[i]["outputSizing"];
			menuSize++;
		}
	}

	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("Listing Member entries.");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(memberTempDataStore, "colDesc");
		selection = inputInt();

		if (selection < memberTempDataStore.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	// Print table headings, and copy into vector space for outputSizing
	int lineSize = 0;
	std::vector<int> outputSizingVector;
	for (int i = 0; i < memberDataStruct.size(); i++) {
		if (memberDataStruct[i]["selected"]) {
			cout << left << std::setw(memberDataStruct[i]["outputSizing"]) << returnString(memberDataStruct[i]["columnDescription"]);

			outputSizingVector.push_back(memberDataStruct[i]["outputSizing"]);

			lineSize += memberDataStruct[i]["outputSizing"];

		}
	}

	cout << endl;

	printLine('=', lineSize);

	// Print table content
	try {
		Session sess = getSessionDb();


		auto myRows = sess.sql("SELECT " + columnNamesGen(memberDataStruct, "selected", "columnName") + " FROM " + thisTableName + " ORDER BY " + returnString(memberTempDataStore[selection]["colName"]))
			.execute();

		int rowCount = 0;
		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(outputSizingVector[i]) << row[i];
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

	cout << endl;
	pause();
}

// Update entry
void memberUpdateEntry() {
	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("Update Member Entries.");
		printLine();
		cout << "Updating will be based on matrix no. Do you want to search user data?" << endl;

		if (!decider()) {
			break;
		}
		memberSearchEntry();
	}


	std::string matrixNo;
	try {
		while (true) {
			system("cls");
			heading("Update Member Entries.");
			printLine();
			cout << "Please input member matrix no to update: ";
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
			menuGen(memberTempDataStore, "colDesc", "notSelected");
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
		cout << "Please input the new data for " << memberTempDataStore[selection]["colDesc"] << endl;
		getline(cin, newData);

		if (noOfChanges > 0) {
			preparedStatement2 += ",";
		}

		preparedStatement2 += returnString(memberTempDataStore[selection]["colName"]) + "=?";

		// Add changes into json
		memberTempDataStore2[noOfChanges]["colDesc"] = memberTempDataStore[selection]["colDesc"];
		memberTempDataStore2[noOfChanges]["colData"] = newData;

		memberTempDataStore[selection]["notSelected"] = false;
		selected.push_back(selection);

		noOfChanges++;

		if (noOfChanges >= memberTempDataStore.size()) {
			break;
		}

		cout << "Do you want to add more data to update?" << endl;

		if (!decider()) {
			break;
		}
	}
	preparedStatement2 += " WHERE matrixNo=?";

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
		auto mySess = sess.sql(preparedStatement2);

		for (int i = 0; i < memberTempDataStore2.size(); i++) {
			mySess = mySess.bind(returnString(memberTempDataStore2[i]["colData"]));
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
void memberDeleteEntry() {
	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("Delete Member Entries.");
		printLine();
		cout << "Deleting will be based on matrix no. Do you want to search user data?" << endl;

		if (!decider()) {
			break;
		}
		memberSearchEntry();
	}


	std::string matrixNo;
	try {
		do {
			system("cls");
			heading("Delete Member Entries.");
			printLine();
			cout << "Please input member matrix no to delete: ";
			getline(cin, matrixNo);

			memberTempDataStore.clear();

			std::string preparedStatement1 = "SELECT " + columnNamesGen(memberDataStruct, "showDuringDeletion", "columnName") + " FROM " + thisTableName + " WHERE matrixNo=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(matrixNo).execute();

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

	std::string preparedStatement2 = "DELETE FROM " + thisTableName + " WHERE matrixNo=?";

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
			memberAddEntry();
			break;
		case 2:
			memberListEntries();
			break;
		case 3:
			memberUpdateEntry();
			break;
		case 4:
			memberDeleteEntry();
			break;
		case 5:
			memberSearchEntry();
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
	}

	cout << endl;
	memberTempDataStore.clear();
	memberTempDataStore2.clear();
	memberTempDataStore3.clear();
	goto MenuStart;
}