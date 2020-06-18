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
	// Show menu top
	heading("ANALYSIS: Member Hostel");
	printLine();

	cout << "No. of Students based on hostel." << endl << endl;

	std::string preparedStatement = "";
	preparedStatement += "SELECT hostel, count(hostel) FROM MEMBER GROUP BY hostel";

	try {
		auto db = getSessionDb();

		auto myResult = db.sql(preparedStatement).execute();

		cout << left << std::setw(50) << "Hostel";
		cout << left << std::setw(50) << "Count";
		cout << endl;
		printLine('=', 100);

		int rowCount = 0;
		for (Row row : myResult.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(50) << row[i];
			}
			cout << endl;

			rowCount++;
		}

		cout << endl;

		cout << "Returned " << rowCount << " results." << endl;

	}
	catch (const mysqlx::Error& err) {
		cout << "ERROR " << err << endl;
	}
	catch (const std::out_of_range& err) {
		cout << "ERROR " << err.what() << endl;
	}
	catch (...) {
		cout << "Unknown error" << endl;
	}
	pause();
}

void countMemberAttendance() {
	// Show menu top
	heading("ANALYSIS: Member Attendance");
	printLine();

	cout << "Do you want to filter by attendance count?" << endl;
	bool filterByCount = decider();
	int myFilter = 0;
	int counter = 0;
	std::string filterByOperatorSys = " WHERE ";
	std::string filterByOperatorUser = "Where";
	if (filterByCount) {
		int selection = 1000;

		while (true) {
			heading("ANALYSIS: Member Attendance - Criteration");
			printLine();

			if (counter > 0) {
				cout << "\nCurrent criteria: " << filterByOperatorUser << endl;
				cout << "\nWould you like an \'OR\' join towards the previous criteria? Default: \'AND\' join" << endl;
				if (decider()) {
					filterByOperatorSys += " OR ";
					filterByOperatorUser += " OR ";
				}
				else {
					filterByOperatorSys += " AND ";
					filterByOperatorUser += " AND ";
				}
			}

			json myJson = { "More than", "Less than", "Equals to" };

			menuGen(myJson);

			cout << endl;
			cout << "Your selection: ";
			selection = inputInt(false, true);

			if (selection < myJson.size()) {
				filterByOperatorSys += " counter";
				filterByOperatorUser += " Attendance ";

				switch (selection)
				{
				case 0:
					filterByOperatorSys += ">";
					filterByOperatorUser += "more than ";
					break;
				case 1:
					filterByOperatorSys += "<";
					filterByOperatorUser += "less than ";
					break;
				case 2:
					filterByOperatorSys += "=";
					filterByOperatorUser += "equals to ";
					break;
				default:
					cout << "Please enter a valid selection." << endl;
					break;
				}
			}
			else {
				cout << "Please enter a valid selection." << endl;
				continue;
			}

			heading("ANALYSIS: Member Attendance - Criteration");
			printLine();

			cout << "Please enter attendance count to be filtered by: \n";
			printLine();
			cout << filterByOperatorUser;
			myFilter = inputInt(false, true);
			filterByOperatorSys += std::to_string(myFilter);
			filterByOperatorUser += std::to_string(myFilter);
			filterByOperatorUser += "\n";

			cout << "Do you want to add criteria?" << endl;
			if (!decider()) {
				break;
			}
			counter++;
		}

	}

	heading("ANALYSIS: Member Attendance");
	printLine();

	cout << "Member's Attendance" << endl << endl;

	std::string preparedStatement = "";
	if (filterByCount) {
		preparedStatement += "SELECT * FROM (SELECT MemberName, MemberMatrixNo, MemberHostel, count(MemberID) as counter FROM ";
		preparedStatement += innerJoin;
		preparedStatement += " GROUP BY MemberID) a ";
		preparedStatement += filterByOperatorSys;

	}
	else {
		preparedStatement += "SELECT MemberName, MemberMatrixNo, MemberHostel, count(MemberID) as counter FROM ";
		preparedStatement += innerJoin;
		preparedStatement += " GROUP BY MemberName, MemberMatrixNo, MemberHostel, MemberID";

	}

	try {
		auto db = getSessionDb();

		auto myResult = db.sql(preparedStatement).execute();

		std::vector<int> setwidth = { 50, 20, 30, 20 };

		cout << left << std::setw(setwidth[0]) << "Name";
		cout << left << std::setw(setwidth[1]) << "Matrix No.";
		cout << left << std::setw(setwidth[2]) << "Hostel";
		cout << left << std::setw(setwidth[3]) << "Attendance Count";
		cout << endl;

		int lineWidth = 0;
		for (int i = 0; i < setwidth.size(); i++) {
			lineWidth += setwidth[i];
		}
		printLine('=', lineWidth);

		int rowCount = 0;
		for (Row row : myResult.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(setwidth[i]) << row[i];
			}
			cout << endl;

			rowCount++;
		}

		cout << endl;

		cout << "Returned " << rowCount << " results." << endl;

	}
	catch (const mysqlx::Error& err) {
		cout << "ERROR " << err << endl;
	}
	catch (const std::out_of_range& err) {
		cout << "ERROR " << err.what() << endl;
	}
	catch (...) {
		cout << "Unknown error" << endl;
	}
	pause();
}

void countUserInput() {
	// Show menu top
	heading("ANALYSIS: User Input");
	printLine();

	cout << "Do you want to group with respect to activity?" << endl;
	bool groupBasedOnActivity = decider();

	std::string preparedStatement = "SELECT ";
	if (groupBasedOnActivity) {
		preparedStatement += "activityName,";
	}
	preparedStatement += " AuthorName, AuthorMatrix, count(userID) FROM ";
	preparedStatement += innerJoin;
	preparedStatement += " GROUP BY userID";
	if (groupBasedOnActivity) {
		preparedStatement += ", activityName";
	}

	heading("ANALYSIS: User Input");
	printLine();
	try {
		auto db = getSessionDb();

		auto myResult = db.sql(preparedStatement).execute();

		std::vector<int> setwidth = {};

		if (groupBasedOnActivity) {
			setwidth = { 40, 40, 20, 20 };
			cout << left << std::setw(40) << "Activity Name";

		}
		else {
			setwidth = { 40, 20, 20 };
		}
		cout << left << std::setw(40) << "Author Name";
		cout << left << std::setw(20) << "Author Matrix";
		cout << left << std::setw(20) << "Input Count";
		cout << endl;

		int lineWidth = 0;
		for (int i = 0; i < setwidth.size(); i++) {
			lineWidth += setwidth[i];
		}
		printLine('=', lineWidth);

		int rowCount = 0;
		for (Row row : myResult.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(setwidth[i]) << row[i];
			}
			cout << endl;

			rowCount++;
		}

		cout << endl;

		cout << "Returned " << rowCount << " results." << endl;

	}
	catch (const mysqlx::Error& err) {
		cout << "ERROR " << err << endl;
	}
	catch (const std::out_of_range& err) {
		cout << "ERROR " << err.what() << endl;
	}
	catch (...) {
		cout << "Unknown error" << endl;
	}
	pause();
}

void countActivityAttendance() {
	// Show menu top
	heading("ANALYSIS: Activity Attendance");
	printLine();

	cout << "Do you want to filter with respect to datetime?" << endl;
	bool filterBasedOnDateTime = decider();


	std::string preparedStatement = "";
	std::string criteria = "";
	if (filterBasedOnDateTime) {
		// To get search criteria
		cout << "Please input the search criteria. You may use SQL-based wildcards like \"%\"." << endl;
		cout << "Date time format is \"YYYY-MM-DD HH:MM\"" << "\n\n> ";

		getline(cin, criteria);

		if (criteria == "") {
			filterBasedOnDateTime = false;
		}
	}


	cout << "Activity's Attendance" << endl << endl;

	if (filterBasedOnDateTime) {
		preparedStatement += "SELECT * FROM (SELECT activityID, activityName, activityDateTime, activityLocation, count(activityID), activityDesc FROM ";
		preparedStatement += innerJoin;
		preparedStatement += " GROUP BY activityID) a WHERE activityDateTime like ?";
	}
	else {
		preparedStatement += "SELECT activityID, activityName, activityDateTime, activityLocation, count(activityID), activityDesc FROM ";
		preparedStatement += innerJoin;
		preparedStatement += " GROUP BY activityID a ";

	}

	//activityDateTime
	try {
		auto db = getSessionDb();

		SqlResult myResult;

		if (filterBasedOnDateTime) {
			myResult = db.sql(preparedStatement).bind(criteria).execute();
		}
		else {
			myResult = db.sql(preparedStatement).execute();
		}

		//.execute();

		std::vector<int> setwidth = { 15, 30, 20, 30, 20, 50 };

		cout << left << std::setw(setwidth[0]) << "Activity ID";
		cout << left << std::setw(setwidth[1]) << "Name";
		cout << left << std::setw(setwidth[2]) << "Date Time";
		cout << left << std::setw(setwidth[3]) << "Location";
		cout << left << std::setw(setwidth[4]) << "Attendance Count";
		cout << left << std::setw(setwidth[5]) << "Activity Description";
		cout << endl;

		int lineWidth = 0;
		for (int i = 0; i < setwidth.size(); i++) {
			lineWidth += setwidth[i];
		}
		printLine('=', lineWidth);

		int rowCount = 0;
		for (Row row : myResult.fetchAll()) {
			for (int i = 0; i < row.colCount(); i++) {
				cout << left << std::setw(setwidth[i]) << row[i];
			}
			cout << endl;

			rowCount++;
		}

		cout << endl;

		cout << "Returned " << rowCount << " results." << endl;

	}
	catch (const mysqlx::Error& err) {
		cout << "ERROR " << err << endl;
	}
	catch (const std::out_of_range& err) {
		cout << "ERROR " << err.what() << endl;
	}
	catch (...) {
		cout << "Unknown error" << endl;
	}
	pause();
}

void countAttendanceCustomGrouping() {
	// Copy into tempDataStore
	int tempCounter = 0;
	for (int i = 0; i < analysisDataStruct.size(); i++) {
		if (analysisDataStruct[i]["groupable"]) {
			analysisTempDataStore[tempCounter]["colName"] = analysisDataStruct[i]["columnName"];
			analysisTempDataStore[tempCounter]["altColName"] = analysisDataStruct[i]["altColumnName"];
			analysisTempDataStore[tempCounter]["colDesc"] = analysisDataStruct[i]["columnDescription"];
			analysisTempDataStore[tempCounter]["groupBy"] = analysisDataStruct[i]["groupBy"];
			analysisTempDataStore[tempCounter]["outputSizing"] = analysisDataStruct[i]["outputSizing"];
			analysisTempDataStore[tempCounter]["notSelected"] = true;

			tempCounter++;
		}
	}

	// Select items to group, adding into vector to detect invalid selections
	std::vector<int> selected;
	std::vector<std::string> groupBys;
	int selection = 0;
	while (true) {
		// Output selection menu
		while (true) {
			heading("ATTENDANCE: Selecting Grouping");
			printLine();
			cout << "Output table will be with respect to sequence." << endl << endl;

			menuGen(analysisTempDataStore, "colDesc", "notSelected");
			selection = inputInt();

			// Check if selection was previously selected
			if ((selection > analysisTempDataStore.size() - 1) || vectorContains(selected, selection)) {
				cout << "Please input a valid selection." << endl;
				pause();
				continue;

			}
			else {
				break;

			}

		}

		analysisTempDataStore[selection]["notSelected"] = false;

		selected.push_back(selection);

		// Push into group by selections
		if (!vectorContains(groupBys, returnString(analysisTempDataStore[selection]["groupBy"]))) {
			groupBys.push_back(returnString(analysisTempDataStore[selection]["groupBy"]));
		}

		// If reached the maximum number of selection, break.
		if (selected.size() >= analysisTempDataStore.size()) {
			break;
		}


		cout << "Do you want to add more groupings?" << endl;
		if (decider()) {
			continue;
		}
		else {
			break;
		}
	}

	std::string preparedStatement = "SELECT * FROM ( SELECT ";
	// Preparing statement
	for (int i = 0; i < selected.size(); i++) {
		preparedStatement += returnString(analysisTempDataStore[selected[i]]["altColName"]) + " AS ";
		preparedStatement += returnString(analysisTempDataStore[selected[i]]["colName"]) + " , ";
	}

	pause();
	preparedStatement += " count(MemberID) AS Count FROM " + innerJoin;
	preparedStatement += " GROUP BY " + groupBys[0];
	for (int i = 1; i < groupBys.size(); i++) {
		preparedStatement += ", " + groupBys[i];
	}
	preparedStatement += ") a";

	// Create headers
	heading("ATTENDANCE: Selecting Grouping");
	printLine();
	int lineLength = 10;
	cout << "Aggregating based on: ";
	for (int i = 0; i < selected.size(); i++) {
		cout << returnString(analysisTempDataStore[selected[i]]["colDesc"]);
		if (i != selected.size() - 1) {
			cout << ", ";
		}

		lineLength += analysisTempDataStore[selected[i]]["outputSizing"];
	}

	cout << endl << endl;
	for (int i = 0; i < selected.size(); i++) {
		cout << left << std::setw(analysisTempDataStore[selected[i]]["outputSizing"]) << returnString(analysisTempDataStore[selected[i]]["colDesc"]);
	}
	cout << left << std::setw(10) << "Count" << endl;
	printLine('=', lineLength);

	try {

		Session sess = getSessionDb();
		auto myRows = sess.sql(preparedStatement).execute();

		int rowCount = 0;
		for (Row row : myRows.fetchAll()) {
			for (int i = 0; i < row.colCount() - 1; i++) {
				cout << left << std::setw(analysisTempDataStore[selected[i]]["outputSizing"]) << row[i];
			}
			cout << left << std::setw(10) << row[row.colCount() - 1];
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
		cout << "An unknown error occured." << endl;
	}
	pause();
}

void analysisMenu() {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = {
		"MEMBER     : No. of Students Based on Hostel",
		"ATTENDANCE : Custom grouping",
		"MEMBER     : Attendance",
		"ATTENDANCE : No. of Entries inputted for each user",
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