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