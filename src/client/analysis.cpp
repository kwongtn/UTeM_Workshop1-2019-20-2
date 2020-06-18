#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
const std::string thisTableName = "ATTENDANCE";
const std::string innerJoin = "(SELECT a.attendanceID, a.userID, a.activityID, a.MemberID, a.MemberName, a.MemberMatrixNo, a.MemberHostel,  a.AuthorName, a.AuthorMatrix, b.activityName, b.activityLocation, b.activityDesc, b.activityYear, b.activityMonth, b.activityDay, b.activityHour, b.activityMinute, concat(activityYear, '-', if(activityMonth<10, concat('0', activityMonth), activityMonth), '-', if(activityDay<10, concat('0', activityDay), activityDay), ' ', if(activityHour<10, concat('0', activityHour), activityHour), ':', if(activityMinute<10, concat('0', activityMinute), activityMinute)) AS activityDateTime FROM ( SELECT a.attendanceID, a.userID, a.activityID, a.MemberName, a.MemberMatrixNo, a.MemberHostel, a.MemberID, b.AuthorName, b.AuthorMatrix  FROM (  SELECT a.attendanceID, a.userID, a.activityID, a.memberID AS MemberID,  b.engName AS MemberName, b.matrixNo AS MemberMatrixNo, b.hostel AS MemberHostel  FROM ATTENDANCE a INNER JOIN MEMBER b ON a.memberID=b.memberID ) a INNER JOIN (  SELECT b.engName AS AuthorName, b.matrixNo AS AuthorMatrix, a.userID      FROM USER a INNER JOIN MEMBER b ON a.memberID=b.memberID ) b ON a.userID=b.userID) a  INNER JOIN ACTIVITY b ON a.activityID=b.activityID) a";

/*
* All values in this table are classificable.
- columnName					: Indicates the derived column name.
- altColumnName				: Indicates the function to derive the column.
- columnDescription		: Indicates the user facing name.
*/
json analysisDataStruct{
	{
		{"columnName", "Qualification"},
		{"altColumnName", "IF(LEFT(MemberMatrixNo, 1)='B', 'Degree', IF(LEFT(MemberMatrixNo, 1)='D', 'Diploma', IF(LEFT(MemberMatrixNo, 1)='M', 'Masters', IF(LEFT(MemberMatrixNo, 1)='G', 'Pre-Postgraduate', IF(LEFT(MemberMatrixNo, 1)='P', 'PhD', 'Unknown')))))"},
		{"columnDescription", "Qualification"},
		{"outputSizing", 20},
		{"showDuringListing", true},
		{"groupBy", "Qualification"},
		{"groupable", true}
	}, {
		{"columnName", "Faculty"},
		{"altColumnName", "IF(SUBSTRING(MemberMatrixNo, 2, 2)='01', 'FKE', IF(SUBSTRING(MemberMatrixNo, 2, 2)='02', 'FKEKK', IF(SUBSTRING(MemberMatrixNo, 2, 2)='03', 'FTMK', IF(SUBSTRING(MemberMatrixNo, 2, 2)='04', 'FKM', IF(SUBSTRING(MemberMatrixNo, 2, 2)='05', 'FKP', IF(SUBSTRING(MemberMatrixNo, 2, 2)='06', 'FPTT', IF(SUBSTRING(MemberMatrixNo, 2, 2)='07', 'FTKEE', IF(SUBSTRING(MemberMatrixNo, 2, 2)='08', 'FTKEE', IF(SUBSTRING(MemberMatrixNo, 2, 2)='09', 'FTKMP', 'Unknown')))))))))"},
		{"columnDescription", "Faculty"},
		{"outputSizing", 10},
		{"showDuringListing", true},
		{"groupBy", "Faculty"},
		{"groupable", true}
	}, {
		{"columnName", "MemberHostel"},
		{"altColumnName", "MemberHostel"},
		{"columnDescription", "Member Hostel"},
		{"outputSizing", 15},
		{"showDuringListing", true},
		{"groupBy", "MemberHostel"},
		{"groupable", true}
	}, {
		{"columnName", "activityName"},
		{"altColumnName", "activityName"},
		{"columnDescription", "Activity Name"},
		{"outputSizing", 20},
		{"showDuringListing", true},
		{"groupBy", "activityID"},
		{"groupable", true}
	}, {
		{"columnName", "activityYear"},
		{"altColumnName", "activityYear"},
		{"columnDescription", "Year"},
		{"outputSizing", 6},
		{"showDuringListing", false},
		{"groupBy", "activityYear"},
		{"groupable", true}
	}, {
		{"columnName", "activityMonth"},
		{"altColumnName", "activityMonth"},
		{"columnDescription", "Month"},
		{"outputSizing", 7},
		{"showDuringListing", false},
		{"groupBy", "activityMonth"},
		{"groupable", true}
	}, {
		{"columnName", "activityDay"},
		{"altColumnName", "activityDay"},
		{"columnDescription", "Day"},
		{"outputSizing", 5},
		{"showDuringListing", false},
		{"groupBy", "activityDay"},
		{"groupable", true}
	}, {
		{"columnName", "activityHour"},
		{"altColumnName", "activityHour"},
		{"columnDescription", "Hour"},
		{"outputSizing", 6},
		{"showDuringListing", false},
		{"groupBy", "activityHour"},
		{"groupable", true}
	}, {
		{"columnName", "activityMinute"},
		{"altColumnName", "activityMinute"},
		{"columnDescription", "Minute"},
		{"outputSizing", 6},
		{"showDuringListing", false},
		{"groupBy", "activityMinute"},
		{"groupable", true}
	}
};


json analysisTempDataStore{};
json analysisTempDataStore2{};
json analysisTempDataStore3{};

void countHostel() {
}

void countMemberAttendance() {
}

void countUserInput() {
}

void countActivityAttendance() {

}

void countAttendanceCustomGrouping() {
}

void analysisMenu() {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = {
		"MEMBER     : No. of Students Based on Hostel",
		"ATTENDANCE : Custom grouping",
		"MEMBER     : Attendance",
		"ATTEND
		ANCE : No. of Entries inputted for each user",
		"ATTENDANCE : For each activity"
	};


	clearScreen();

	// Show menu top
	heading("ANALYSIS Menu");
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
			countHostel();
			break;
		case 2:
			countAttendanceCustomGrouping();
			break;
		case 3:
			countMemberAttendance();
			break;
		case 4:
			countUserInput();
			break;
		case 5:
			countActivityAttendance();
			break;
			/*
				case 6:
					attendanceListDetail();
					break;
*/
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
	analysisTempDataStore.clear();
	analysisTempDataStore2.clear();
	analysisTempDataStore3.clear();
	goto MenuStart;
}