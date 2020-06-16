#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
void memberListEntries();
void memberSearchEntry();
void activityListEntries();
void activitySearchEntry();
std::string columnNamesGen(json, std::string, std::string, std::string wrapper = "");
const std::string thisTableName = "ATTENDANCE";
const std::string innerJoin = "(SELECT a.attendanceID, a.userID, a.activityID, a.MemberName, a.MemberMatrixNo, a.MemberHostel,  a.AuthorName, a.AuthorMatrix, b.activityName, b.activityLocation, b.activityDesc, b.activityYear, b.activityMonth, b.activityDay, b.activityHour, b.activityMinute FROM ( SELECT a.attendanceID, a.userID, a.activityID, a.MemberName, a.MemberMatrixNo, a.MemberHostel,  b.AuthorName, b.AuthorMatrix  FROM (  SELECT a.attendanceID, a.userID, a.activityID,   b.engName AS MemberName, b.matrixNo AS MemberMatrixNo, b.hostel AS MemberHostel  FROM ATTENDANCE a INNER JOIN MEMBER b ON a.memberID=b.memberID ) a INNER JOIN (  SELECT b.engName AS AuthorName, b.matrixNo AS AuthorMatrix, a.userID      FROM USER a INNER JOIN MEMBER b ON a.memberID=b.memberID ) b ON a.userID=b.userID) a  INNER JOIN ACTIVITY b ON a.activityID=b.activityID) a";

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
json attendanceDataStruct{
	{
		{"columnName", "userID"},
		{"altColumnName", "userID"},
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
	}, {
		{"columnName", "activityID"},
		{"altColumnName", "activityID"},
		{"columnDescription", "Activity ID"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", false},
		{"searchable", false},
		{"showDuringDeletion", true},
		{"outputSizing", 10},
		{"updatable", false},
		{"isUnique", true},
		{"inThisTable", true},
		{"orderable", true},
		{"isInteger", true}
	}, {
		{"columnName", "MemberName"},
		{"altColumnName", "MemberName"},
		{"columnDescription", "Member Name"},
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
		{"isInteger", false}
	}, {
		{"columnName", "MemberMatrixNo"},
		{"altColumnName", "MemberMatrixNo"},
		{"columnDescription", "Member Matrix No"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 15},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	}, {
		{"columnName", "MemberHostel"},
		{"altColumnName", "MemberHostel"},
		{"columnDescription", "Member Hostel"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 10},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	}, {
		{"columnName", "AuthorName"},
		{"altColumnName", "AuthorName"},
		{"columnDescription", "Input User"},
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
		{"isInteger", false}
	}, {
		{"columnName", "AuthorMatrix"},
		{"altColumnName", "AuthorMatrix"},
		{"columnDescription", "Input User Matrix No"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 15},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	}, {
		{"columnName", "activityID"},
		{"altColumnName", "activityID"},
		{"columnDescription", "Activity ID"},
		{"input", true},
		{"compulsoryInput", true},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 5},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	}, {
		{"columnName", "activityName"},
		{"altColumnName", "activityName"},
		{"columnDescription", "Activity Name"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 15},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	},{
		{"columnName", "concat(activityYear, \"-\", if(activityMonth<10, concat(\"0\", activityMonth), activityMonth), \"-\", if(activityDay<10, concat(\"0\", activityDay), activityDay), \" \", if(activityHour<10, concat(\"0\", activityHour), activityHour), \":\", if(activityMinute<10, concat(\"0\", activityMinute), activityMinute)) AS DateTime"},
		{"altColumnName", "concat(activityYear, \"-\", if(activityMonth<10, concat(\"0\", activityMonth), activityMonth), \"-\", if(activityDay<10, concat(\"0\", activityDay), activityDay), \" \", if(activityHour<10, concat(\"0\", activityHour), activityHour), \":\", if(activityMinute<10, concat(\"0\", activityMinute), activityMinute)) AS DateTime"},
		{"columnDescription", "Activity DateTime"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 20},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	}, {
		{"columnName", "activityLocation"},
		{"altColumnName", "activityLocation"},
		{"columnDescription", "Activity Location"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 15},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", true},
		{"isInteger", false}
	}, {
		{"columnName", "activityDesc"},
		{"altColumnName", "activityDesc"},
		{"columnDescription", "Activity Description"},
		{"input", false},
		{"compulsoryInput", false},
		{"selected", true},
		{"searchable", true},
		{"showDuringDeletion", true},
		{"outputSizing", 45},
		{"updatable", false},
		{"isUnique", false},
		{"inThisTable", false},
		{"orderable", false},
		{"isInteger", false}
	}

};

json attendanceTempDataStore{};
json attendanceTempDataStore2{};
json attendanceTempDataStore3{};

void attendanceAddEntry(int userID){

}

void attendanceBatchAdd(int userID){}

void attendanceSearchEntry(){}

void attendanceDeleteEntry(){}

void attendanceListDetail() {}

void attendanceList() {}

void attendanceMenu(int userID) {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = { "Add Attendance", "Batch Add Attendance", "Delete Attendance", "Search attendance", "List Attendance", "Get Detailed Information" };


	clearScreen();

	// Show menu top
	heading("ATTENDANCE Management Menu");
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
			attendanceAddEntry(userID);
			break;
		case 2:
			attendanceBatchAdd(userID);
			break;
		case 3:
			attendanceDeleteEntry();
			break;
		case 4:
			// attendanceSearchEntry();
			break;
		case 5:
			attendanceList();
			break;
		case 6:
			attendanceListDetail();
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
	attendanceTempDataStore.clear();
	attendanceTempDataStore2.clear();
	attendanceTempDataStore3.clear();
	goto MenuStart;
}