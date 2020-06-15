#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
std::string columnNamesGen(json, std::string, std::string, std::string wrapper = "");
const std::string thisTableName = "ACTIVITY";
const std::string innerJoin = "ACTIVITY a INNER JOIN (SELECT a.memberID, a.engName, a.matrixNo, a.hostel, b.userID FROM MEMBER a INNER JOIN USER b ON a.memberID=b.memberID) b ON a.userID=b.userID";

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
json activityDataStruct{
	{
		{"columnName", "userID"},
		{"altColumnName", "a.userID"},
		{"columnDescription", "User ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", false},
		{"outputSizing", 10},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", true},
		{"orderable", false},
		{"isInteger", true}
	},{
		{"columnName", "activityID"},
		{"altColumnName", "a.activityID"},
		{"columnDescription", "ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 5},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	}, {
		{"columnName", "activityName"},
		{"altColumnName", "a.activityName"},
		{"columnDescription", "Name"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 20},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", false}
	},{
		{"columnName", "activityYear"},
		{"altColumnName", "a.activityYear"},
		{"columnDescription", "Year"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", false},
		{"searchable", true},
		{"showDuringDeletion", false},
		{"outputSizing", 6},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	},{
		{"columnName", "activityMonth"},
		{"altColumnName", "a.activityMonth"},
		{"columnDescription", "Month"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", false},
		{"searchable", true},
		{"showDuringDeletion", false},
		{"outputSizing", 7},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	},{
		{"columnName", "activityDay"},
		{"altColumnName", "a.activityDay"},
		{"columnDescription", "Day"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", false},
		{"searchable", true},
		{"showDuringDeletion", false},
		{"outputSizing", 5},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	},{
		{"columnName", "activityHour"},
		{"altColumnName", "a.activityHour"},
		{"columnDescription", "Hour"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", false},
		{"searchable", true},
		{"showDuringDeletion", false},
		{"outputSizing", 5},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	},{
		{"columnName", "activityMinute"},
		{"altColumnName", "a.activityMinute"},
		{"columnDescription", "Minute"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", false},
		{"searchable", true},
		{"showDuringDeletion", false},
		{"outputSizing", 8},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	},{
		{"columnName", "activityLocation"},
		{"altColumnName", "a.activityLocation"},
		{"columnDescription", "Location"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 20},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", false}
	},{
		{"columnName", "concat(activityYear, \"-\", if(activityMonth<10, concat(\"0\", activityMonth), activityMonth), \"-\", if(activityDay<10, concat(\"0\", activityDay), activityDay), \" \", if(activityHour<10, concat(\"0\", activityHour), activityHour), \":\", if(activityMinute<10, concat(\"0\", activityMinute), activityMinute)) AS DateTime"},
		{"altColumnName", "concat(a.activityYear, \"-\", if(a.activityMonth<10, concat(\"0\", a.activityMonth), a.activityMonth), \"-\", if(a.activityDay<10, concat(\"0\", a.activityDay), a.activityDay), \" \", if(a.activityHour<10, concat(\"0\", a.activityHour), a.activityHour), \":\", if(a.activityMinute<10, concat(\"0\", a.activityMinute), a.activityMinute)) AS DateTime"},
		{"columnDescription", "Datetime"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 20},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", false},
		{"isInteger", false}
	}, {
		{"columnName", "engName"},
		{"altColumnName", "b.engName"},
		{"columnDescription", "Author"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 20},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", true}
	}, {
		{"columnName", "activityDesc"},
		{"altColumnName", "a.activityDesc"},
		{"columnDescription", "Description"},
		{"input", true},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 35},
		{"updatable", true},
		{"isUnique", false},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", false}
	}

};

json activityTempDataStore{};
json activityTempDataStore2{};
json activityTempDataStore3{};

void activityListEntries() {
	// Copy relavant rows to tempDataStore
	int menuSize = 0;
	for (int i = 0; i < activityDataStruct.size(); i++) {
		if (activityDataStruct[i]["orderable"]) {
			activityTempDataStore[menuSize]["colDesc"] = activityDataStruct[i]["columnDescription"];
			activityTempDataStore[menuSize]["colName"] = activityDataStruct[i]["altColumnName"];
			activityTempDataStore[menuSize]["outputSizing"] = activityDataStruct[i]["outputSizing"];
			menuSize++;
		}
	}

	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("Listing Activity entries.");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(activityTempDataStore, "colDesc");
		selection = inputInt();

		if (selection < activityTempDataStore.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	heading("Listing Activity entries.");
	printLine();

	// Print table headings, and copy into vector space for outputSizing
	int lineSize = 0;
	std::vector<int> outputSizingVector;
	for (int i = 0; i < activityDataStruct.size(); i++) {
		if (activityDataStruct[i]["selected"]) {
			cout << left << std::setw(activityDataStruct[i]["outputSizing"]) << returnString(activityDataStruct[i]["columnDescription"]);

			outputSizingVector.push_back(activityDataStruct[i]["outputSizing"]);

			lineSize += activityDataStruct[i]["outputSizing"];

		}
	}

	cout << endl;

	printLine('=', lineSize);

	// Print table content
	try {
		Session sess = getSessionDb();

		std::string preparedStatement = "SELECT " + columnNamesGen(activityDataStruct, "selected", "altColumnName") + " FROM " + innerJoin + " ORDER BY " + returnString(activityTempDataStore[selection]["colName"]);

		auto myRows = sess.sql(preparedStatement)
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

void activityAddEntry(int userID) {
	heading("Activity Creation");
	printLine();
	cout << "Please input the following data to facilitate for activity creation.\n* Indicates that entries with that value must be unique." << endl << endl;

	int tempCounter = 0;
	for (int i = 0; i < activityDataStruct.size(); i++) {

		std::string temp = "";

		if (activityDataStruct[i]["input"]) {
			bool x = true;
			while (x) {
				std::string currString = returnString(activityDataStruct[i]["columnDescription"]);
				if (activityDataStruct[i]["isUnique"]) {
					currString += "*";
				}

				cout << left << std::setw(30) << currString << "\t: ";

				if (activityDataStruct[i]["isInteger"]) {
					int inputData = -1000;
					inputData = inputInt(false, activityDataStruct[i]["compulsoryInput"]);

					if (inputData == -1000) {
						temp = "";
					}
					else {
						temp = std::to_string(inputData);
					}
				
				}
				else {
					getline(cin, temp);

				}


				if (activityDataStruct[i]["compulsoryInput"] && temp == "") {
					cout << "Please input a value." << endl;
				}
				else {
					if (temp != "") {
						activityTempDataStore[tempCounter]["colName"] = activityDataStruct[i]["columnName"];
						activityTempDataStore[tempCounter]["colValue"] = temp;
						activityTempDataStore[tempCounter]["getThis"] = true;

					}
					x = false;
				}

			}

			tempCounter++;

		}
	}


	std::string preparedStatement = "INSERT INTO " + thisTableName + " (userID, ";
	preparedStatement += columnNamesGen(activityTempDataStore, "getThis", "colName");
	preparedStatement += ") VALUES (" + std::to_string(userID) +  ", ?";

	for (int i = 1; i < activityTempDataStore.size(); i++) {
		preparedStatement += ", ?";
	}
	preparedStatement += ")";

	bool recover = true;
	while (recover) {
		try {
			Session sess = getSessionDb();
			cout << preparedStatement << endl;
			auto mySess = sess.sql(preparedStatement);

			for (int i = 0; i < activityTempDataStore.size(); i++) {
				mySess = mySess.bind(returnString(activityTempDataStore[i]["colValue"]));
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

void activityDeleteEntry() {

	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("Delete Activity Entries.");
		printLine();
		cout << "Deleting will be based on activity ID. Do you want to search activity data?" << endl;

		if (!decider()) {
			break;
		}
		activitySearchEntry();
	}


	std::string activityID;
	try {
		do {
			system("cls");
			heading("Delete Activity Entries.");
			printLine();
			cout << "Please input activity ID to delete: ";
			getline(cin, activityID);

			activityTempDataStore.clear();

			std::string preparedStatement1 = "SELECT " + columnNamesGen(activityDataStruct, "showDuringDeletion", "altColumnName") + " FROM " + innerJoin + " WHERE activityID=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(activityID).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				cout << "Are you sure you want to delete the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << left << std::setw(30) << returnString(activityDataStruct[i]["columnDescription"]) << "\t: ";
						cout << row[i] << endl;
					}
					cout << endl;
				}
				break;
			}
			else {
				cout << "No member with activity ID " << activityID << " found." << endl;
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

	std::string preparedStatement2 = "DELETE FROM " + thisTableName + " WHERE activityID=?";

	if (decider()) {
		Session sess = getSessionDb();
		auto myRows = sess.sql(preparedStatement2).bind(activityID).execute();

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

void activityMenu(int userID) {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = { "Add Activity", "List Activities", "Update Activity", "Delete Activity", "Search Activity" };


	clearScreen();

	// Show menu top
	heading("ACTIVITY Management Menu");
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
			activityAddEntry(userID);
			break;
		case 2:
			activityListEntries();
			break;
		case 3:
			activityUpdateEntry(userID);
			break;
		case 4:
			activityDeleteEntry();
			break;
		case 5:
			activitySearchEntry();
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
	activityTempDataStore.clear();
	activityTempDataStore2.clear();
	activityTempDataStore3.clear();
	goto MenuStart;
}