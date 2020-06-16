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

void attendanceListDetail() {
	// Copies relavant data to attendanceTempDataStore3
	int tempCounter = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["showDuringDeletion"]) {
			attendanceTempDataStore3[tempCounter]["colName"] = attendanceDataStruct[i]["altColumnName"];
			attendanceTempDataStore3[tempCounter]["colDesc"] = attendanceDataStruct[i]["columnDescription"];
			attendanceTempDataStore3[tempCounter]["outputSizing"] = attendanceDataStruct[i]["outputSizing"];
			attendanceTempDataStore3[tempCounter]["showDuringDeletion"] = attendanceDataStruct[i]["showDuringDeletion"];

			tempCounter++;
		}
	}

	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("Show Detailed Attendance Entries");
		printLine();
		cout << "Detailed information will be shown based on attendance ID. Do you want to search attendance data?" << endl;

		if (!decider()) {
			break;
		}
		attendanceSearchEntry();
	}


	std::string attendanceID;
	try {
		while (true) {
			system("cls");
			heading("Show Detailed Activity Entries");
			printLine();
			cout << "Please input activity ID to show: ";
			attendanceID = std::to_string(inputInt(false, true));

			std::string preparedStatement1 = "SELECT " + columnNamesGen(attendanceTempDataStore3, "showDuringDeletion", "colName") + " FROM " + innerJoin + " WHERE attendanceID=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(attendanceID).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << left << std::setw(20) << returnString(attendanceTempDataStore3[i]["colDesc"]) << "\t: ";
						cout << row[i] << endl;
					}
					cout << endl;
				}

				pause();
				return;
			}
			else {
				cout << "No member with attendance ID " << attendanceID << " found." << endl;
				cout << "Try again?" << endl;

				if (!decider()) {
					return;
				}
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
		cout << "Activity Info: Unknown Error";
		pause();
	}
}

void attendanceList() {
	// Copy relavant rows to tempDataStore
	int menuSize = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["orderable"]) {
			attendanceTempDataStore[menuSize]["colDesc"] = attendanceDataStruct[i]["columnDescription"];
			attendanceTempDataStore[menuSize]["colName"] = attendanceDataStruct[i]["columnName"];
			attendanceTempDataStore[menuSize]["outputSizing"] = attendanceDataStruct[i]["outputSizing"];
			menuSize++;
		}
	}

	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("Listing Member entries.");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(attendanceTempDataStore, "colDesc");
		selection = inputInt();

		if (selection < attendanceTempDataStore.size()) {
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
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["selected"]) {
			cout << left << std::setw(attendanceDataStruct[i]["outputSizing"]) << returnString(attendanceDataStruct[i]["columnDescription"]);

			outputSizingVector.push_back(attendanceDataStruct[i]["outputSizing"]);

			lineSize += attendanceDataStruct[i]["outputSizing"];

		}
	}

	cout << endl;

	printLine('=', lineSize);

	// Print table content
	try {
		Session sess = getSessionDb();

		std::string preparedStatement = "SELECT " + columnNamesGen(attendanceDataStruct, "selected", "columnName") + " FROM " + innerJoin + " ORDER BY " + returnString(attendanceTempDataStore[selection]["colName"]);

		auto myRows = sess.sql(preparedStatement).execute();

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