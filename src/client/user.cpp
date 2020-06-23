#include "utils.h"
#include "sha256.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
std::string columnNamesGen(json, std::string, std::string, std::string wrapper = "");
const std::string thisTableName = "USER";
const std::string innerJoin = "USER a INNER JOIN MEMBER b ON a.memberID=b.memberID";


/*
- columnName					: Indicates the column name on its own table.
- altColumnName				: Indicates the column name should it is being joined to other tables.
- columnDescription		: Indicates the user facing name.
- input								: Indicates whether users are allowed to input during entry creation.
- compulsoryInput			: Indicates whether the column must be filled in during entry creation.
- selected						: Indicates whether the column will be shown during listing.
- searchable					: Indicates whether searches by that column will be allowed.
- showDuringDeletion	: Indicates whether the column will be shown during deletion.
- outputSizing				: Indicates the size of output in fixed width constraint situations.
- updatable						: Indicates whether the column is updatable.
- isUnique						: Indicates whether a column's value must be unique.
- inThisTable					: Indicates whether a column exists in the table defined by 'thisTableName'.
- orderable						: Whether ordering by this column is allowed.
*/
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
		{"inThisTable", true},
		{"orderable", true}
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
		{"inThisTable", true},
		{"orderable", true}
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
		{"orderable", true},
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
		{"inThisTable", true},
		{"orderable", false}
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
		{"orderable", true},
		{"correspondingTable", "MEMBER"},
		{"localJoin", "memberID"},
		{"externalJoin", "memberID"}
	}

};

json userTempDataStore{};
json userTempDataStore2{};
json userTempDataStore3{};

// Search entry
void userSearchEntry() {
	// Copies searchable items to userTempDataStore
	int tempCounter = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["searchable"]) {
			userTempDataStore[tempCounter]["colName"] = userDataStruct[i]["altColumnName"];
			userTempDataStore[tempCounter]["colDesc"] = userDataStruct[i]["columnDescription"];
			userTempDataStore[tempCounter]["outputSizing"] = userDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	// Copies orderable items to userTempDataStore2
	tempCounter = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["orderable"]) {
			userTempDataStore2[tempCounter]["colName"] = userDataStruct[i]["altColumnName"];
			userTempDataStore2[tempCounter]["colDesc"] = userDataStruct[i]["columnDescription"];
			userTempDataStore2[tempCounter]["outputSizing"] = userDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	// Copies listable items to userTempDataStore3
	tempCounter = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["selected"]) {
			userTempDataStore3[tempCounter]["colName"] = userDataStruct[i]["altColumnName"];
			userTempDataStore3[tempCounter]["colDesc"] = userDataStruct[i]["columnDescription"];
			userTempDataStore3[tempCounter]["outputSizing"] = userDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	std::string preparedStatement = "SELECT " + columnNamesGen(userDataStruct, "selected", "altColumnName") + " FROM " + innerJoin + " WHERE ";

	int counter = 0;
	std::string criteriaStringUser = "Criteria: SELECT WHERE ";
	std::string criteriaStringSys = "";
	std::vector<std::string> criterias;

	do {
		if (counter > 0) {
			while (true) {
				heading("USER > Search > Criteria Generation > OR/AND Selection");
				printLine();
				cout << "\nCurrent " << criteriaStringUser << endl;
				cout << "\nWould you like an \'OR\' join  or \'AND\' join towards the previous criteria? " << endl;
				cout << 0 << "\t:" << "AND join" << endl;
				cout << 1 << "\t:" << "OR join" << endl << endl;
				cout << "Your choice: ";
				int choice = inputInt(false);

				if (choice == 0 || choice == 1) {
					if (choice == 0) {
						criteriaStringSys += " AND ";
						criteriaStringUser += " AND ";
					}
					else {
						criteriaStringSys += " OR ";
						criteriaStringUser += " OR ";
					}
					break;
				}
				else {
					if (choice == -1) {
						return;
					}
					cout << "Input error. Please try again." << endl;
					pause();
				}

			}
		}

		heading("USER > Search > Criteria Generation > Column Selection");
		printLine();
		menuGen(userTempDataStore, "colDesc");

		if (counter > 0) {
			cout << "\nCurrent " << criteriaStringUser << endl;

		}

		int selection;
		while (true) {
			cout << "\nPlease select the column you would like to search by: ";
			try {
				selection = inputInt();

				// Return to menu if user entered "-1"
				if (selection == -1) return;

				if (selection > userTempDataStore.size() || selection < 0) {
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

		// Search criteria input.
		heading("USER > Search > Criteria Generation > Column Selection > Search Statement Generation");
		printLine();
		if (counter > 0) {
			cout << "\nCurrent " << criteriaStringUser << endl << endl;

		}
		cout << "Selected " << userTempDataStore[selection]["colDesc"] << endl;

		// To get search criteria
		cout << "Please input the search criteria. You may use SQL-based wildcards like \"%\"\n\n> ";

		std::string criteria = "";
		getline(cin, criteria);

		// Return to menu if user entered "-1"
		if (criteria == "-1") return;

		criterias.push_back(criteria);
		criteriaStringUser += userTempDataStore[selection]["colDesc"];
		criteriaStringUser += " is \"" + criteria + "\" \n";

		cout << "\n\n" << criteriaStringUser;


		criteriaStringSys += returnString(userTempDataStore[selection]["colName"]) + " like ?";

		counter++;

		cout << "\nWould you like to add criteria? " << endl;

	} while (decider());


	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("MEMBER > Search > Criteria Generation > Ordering Selection");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(userTempDataStore2, "colDesc");
		selection = inputInt();

		// Return to menu if user entered "-1"
		if (selection == -1) return;

		if (selection < userTempDataStore2.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	heading("MEMBER > Search > Result");
	printLine();
	cout << "Search statement " << criteriaStringUser << endl;

	preparedStatement += criteriaStringSys + " ORDER BY " + returnString(userTempDataStore2[selection]["colName"]);


	// Print table headings
	int lineSize = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["selected"]) {
			cout << left << std::setw(userDataStruct[i]["outputSizing"]) << returnString(userDataStruct[i]["columnDescription"]);

			lineSize += userDataStruct[i]["outputSizing"];

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
				cout << left << std::setw(userTempDataStore3[i]["outputSizing"]) << row[i];
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
void userAddEntry() {
	bool recover = true;
	int memberID;
	std::string matrixNo;
	// Getting Matrix No
	while (true) {
		heading("USER > Add Entry");
		printLine();
		cout << "Please input the following data to facilitate for user creation.\n\nAn asterisk (*) indicates entries with mandatory input." << endl << endl;
		cout << left << std::setw(30) << "Matrix No.*" << "\t: ";
		getline(cin, matrixNo);

		// Return to menu if user entered "-1"
		if (matrixNo == "-1") return;

		try {
			Session sess = getSessionDb();

			// Check if user already exist
			auto myRows1 = sess.sql("SELECT a.userID FROM " + innerJoin + " WHERE b.matrixNo=?").bind(matrixNo).execute();

			if (myRows1.count() == 0) {
				auto myRows2 = sess.sql("SELECT memberID FROM MEMBER WHERE matrixNo=?").bind(matrixNo).execute();
				if (myRows2.count() == 0) {
					cout << "Member with matrix no. " << matrixNo << " does not exist. Returning to menu." << endl;
					pause();
					return;
				}

				auto myRow2 = myRows2.fetchOne();

				std::stringstream ss1;
				myRow2.get(0).print(ss1);
				memberID = std::stoi(ss1.str());

				break;
			}
			else {
				cout << "User already exist. Returning to menu." << endl;
				pause();
				return;

			}
		}
		catch (const mysqlx::Error& err)
		{
			cout << "ERROR: " << err << endl;
			cout << "Do you want to try database action again?" << endl;
			if (!decider()) {
				return;
			}
		}
		catch (...) {
			cout << "Unknown Error";
			cout << "Do you want to try database action again?" << endl;
			if (!decider()) {
				return;
			}
		}
	}


	std::string password = "";
	std::string salt = sha256(random_string());

	while (true) {
		cout << left << std::setw(30) << "Password*" << "\t: ";
		getline(cin, password);

		// Return to menu if user entered "-1"
		if (password == "-1") return;

		if (password == "") {
			cout << "Please enter a password." << endl;
			pause();
		}
		else {
			break;
		}

	}

	password = sha256(salt + password);


	std::string preparedStatement1 = "INSERT INTO " + thisTableName + " (memberID, pw, salt) VALUES (?, ?, ?)";

	recover = true;
	while (recover) {
		try {
			Session sess = getSessionDb();

			auto mySess = sess.sql(preparedStatement1).bind(memberID).bind(password).bind(salt);

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
void userListEntries() {
	// Copy relavant rows to tempDataStore
	int menuSize = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["orderable"]) {
			userTempDataStore[menuSize]["colDesc"] = userDataStruct[i]["columnDescription"];
			userTempDataStore[menuSize]["colName"] = userDataStruct[i]["altColumnName"];
			userTempDataStore[menuSize]["outputSizing"] = userDataStruct[i]["outputSizing"];
			menuSize++;
		}
	}

	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("USER > Listing > Ordering");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(userTempDataStore, "colDesc");
		selection = inputInt();

		// Return to menu if user entered "-1"
		if (selection == -1) return;

		if (selection < userTempDataStore.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	heading("USER > Listing > Results");
	printLine();

	// Print table headings, and copy into vector space for outputSizing
	int lineSize = 0;
	std::vector<int> outputSizingVector;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["selected"]) {
			cout << left << std::setw(userDataStruct[i]["outputSizing"]) << returnString(userDataStruct[i]["columnDescription"]);

			outputSizingVector.push_back(userDataStruct[i]["outputSizing"]);

			lineSize += userDataStruct[i]["outputSizing"];

		}
	}

	cout << endl;

	printLine('=', lineSize);

	// Print table content
	try {
		Session sess = getSessionDb();


		auto myRows = sess.sql("SELECT " + columnNamesGen(userDataStruct, "selected", "altColumnName") + " FROM " + innerJoin + " ORDER BY " + returnString(userTempDataStore[selection]["colName"]))
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
void userUpdateEntry() {
	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("USER > Update");
		printLine();
		cout << "Updating will be based on matrix no. Do you want to search user data?" << endl;

		if (!decider()) {
			break;
		}
		userSearchEntry();
	}


	std::string matrixNo;
	try {
		while (true) {
			heading("USER > Update > Input Matrix No.");
			printLine();
			cout << "Please input member matrix no to update: ";
			getline(cin, matrixNo);

			// Return to menu if user entered "-1"
			if (matrixNo == "-1") return;

			std::string preparedStatement1 = "SELECT " + columnNamesGen(userDataStruct, "showDuringDeletion", "altColumnName") + " FROM " + innerJoin + " WHERE a.matrixNo=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(matrixNo).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				heading("USER > Update > User Confirmation");
				printLine();
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
		pause();
	}
	catch (...) {
		cout << "Unknown Error";
		pause();
	}

	std::string password = "";
	std::string salt = sha256(random_string());
	while (true) {
		heading("USER > Update Password");
		printLine();
		cout << "Please enter new password: ";
		getline(cin, password);

		// Return to menu if user entered "-1"
		if (password == "-1") return;

		if (password == "") {
			cout << "Please enter a value for password" << endl;
			pause();
		}
		else {
			break;
		}
	}

	password = sha256(salt + password);

	std::string preparedStatement2 = "UPDATE " + thisTableName + " SET salt=?, password=?";
	preparedStatement2 += " WHERE memberID=(SELECT memberID FROM MEMBER WHERE matrixNo=?)";

	// Show current changes
	heading("USER > Update Password > Confirmation");
	printLine();
	cout << "Are you sure you want to update password?" << endl;

	if (decider()) {
		Session sess = getSessionDb();
		auto mySess = sess.sql(preparedStatement2).bind(salt, password, matrixNo);

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
void userDeleteEntry() {
	// Copy relavant data to userTempDataStore
	int tempCounter = 0;
	for (int i = 0; i < userDataStruct.size(); i++) {
		if (userDataStruct[i]["showDuringDeletion"]) {
			userTempDataStore[tempCounter]["colDesc"] = userDataStruct[i]["columnDescription"];
			userTempDataStore[tempCounter]["altColumnName"] = userDataStruct[i]["altColumnName"];
			userTempDataStore[tempCounter]["showDuringDeletion"] = userDataStruct[i]["showDuringDeletion"];
		}
	}

	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("USER > Delete Entry");
		printLine();
		cout << "Deleting will be based on matrix no. Do you want to search user data?" << endl;

		if (!decider()) {
			break;
		}
		userSearchEntry();
	}


	std::string matrixNo;
	try {
		while (true) {
			heading("USER > Delete Entry > Data Collection");
			printLine();
			cout << "Please input member matrix no to delete: ";
			getline(cin, matrixNo);

			// Return to menu if user entered "-1"
			if (matrixNo == "-1") return;

			std::string preparedStatement1 = "SELECT " + columnNamesGen(userTempDataStore, "showDuringDeletion", "altColumnName") + " FROM " + innerJoin + " WHERE b.matrixNo=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(matrixNo).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				cout << "Are you sure you want to delete the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << left << std::setw(30) << returnString(userTempDataStore[i]["colDesc"]) << "\t: ";
						cout << row[i] << endl;
					}
					cout << endl;
				}
				break;
			}
			else {
				cout << "No member with matrix no. " << matrixNo << " found." << endl;
				cout << "Try again?" << endl;
				if (decider()) {
					continue;
				}
				else {
					cout << "Returning to main menu." << endl;
					pause();
					return;
				}
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
	json menuEntries = { "Add User", "List Users", "Update User Password", "Delete User", "Search User" };

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
		selection = inputInt();
		if (selection > menuEntries.size() || selection < 0) {
			if (selection != 10) {
				throw "Error";
			}
		}

		switch (selection)
		{
		case 1:
			userAddEntry();
			break;
		case 2:
			userListEntries();
			break;
		case 3:
			userUpdateEntry();
			break;
		case 4:
			userDeleteEntry();
			break;
		case 5:
			userSearchEntry();
			break;
		case 10:
			return;
			break;
		case -1:
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
	userTempDataStore.clear();
	userTempDataStore2.clear();
	userTempDataStore3.clear();
	goto MenuStart;
}