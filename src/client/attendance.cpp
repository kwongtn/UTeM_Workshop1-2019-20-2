#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
void memberListEntries();
void memberSearchEntry();
void activityAddEntry(int);
void activityListEntries();
void activitySearchEntry();
void memberAddEntry();
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
		{"columnName", "attendanceID"},
		{"altColumnName", "attendanceID"},
		{"columnDescription", "Attendance ID"},
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
	},{
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
		{"columnName", "concat(activityYear, \"-\", if(activityMonth<10, concat(\"0\", activityMonth), activityMonth), \"-\", if(activityDay<10, concat(\"0\", activityDay), activityDay), \" \", if(activityHour<10, concat(\"0\", activityHour), activityHour), \":\", if(activityMinute<10, concat(\"0\", activityMinute), activityMinute))"},
		{"altColumnName", "concat(activityYear, \"-\", if(activityMonth<10, concat(\"0\", activityMonth), activityMonth), \"-\", if(activityDay<10, concat(\"0\", activityDay), activityDay), \" \", if(activityHour<10, concat(\"0\", activityHour), activityHour), \":\", if(activityMinute<10, concat(\"0\", activityMinute), activityMinute))"},
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

void attendanceAddEntry(int userID) {
	// Check if user wants to search for activity ID.
	while (true) {
		heading("ATTENDANCE > Add Entry");
		printLine();

		cout << "Before adding data you may want to search for the activity ID. Do you want to do so?" << endl;
		if (decider()) {
			while (true) {
				heading("ATTENDANCE > Add Entry > Search Selection");
				printLine();
				cout << "Enter \'1\' to list all entries, or \'2\' to fine tune your search. " << endl;
				int myInt = inputInt();

				// Return to menu if user entered "-1"
				if (myInt == -1) return;

				if (myInt == 1) {
					activityListEntries();
					break;
				}
				else if (myInt == 2) {
					activitySearchEntry();
					break;
				}
				else {
					cout << "Invalid option. Please re-input." << endl;
					pause();
				}

			}

		}
		else {
			break;
		}

	}

	heading("ATTENDANCE > Add Entry");
	printLine();
	cout << "Please input the following data to facilitate for attendance entry creation.\n\nAn asterisk (*) indicates entries with mandatory input." << endl << endl;

	bool recover = true;
	int memberID = 0;
	// Getting memberID
	while (recover) {
		std::string matrixNo;
		cout << left << std::setw(30) << "Matrix No. *" << "\t: ";
		getline(cin, matrixNo);

		// Return to menu if user entered "-1"
		if (matrixNo == "-1") return;

		try {
			Session sess = getSessionDb();

			// Check if member exists
			auto myRows1 = sess.sql("SELECT * FROM MEMBER WHERE matrixNo=?").bind(matrixNo).execute();

			if (myRows1.count() == 0) {
				cout << "Member does not exist. Do you want to re-input?" << endl;
				if (decider()) {
					continue;
				}
				else {
					return;

				}
			}
			else {
				// Get memberID if exist
				auto myRows2 = sess.sql("SELECT memberID FROM MEMBER WHERE matrixNo=?").bind(matrixNo).execute();

				auto myRow2 = myRows2.fetchOne();

				std::stringstream ss1;
				myRow2.get(0).print(ss1);
				memberID = std::stoi(ss1.str());

				break;

			}

		}
		catch (const mysqlx::Error& err)
		{
			cout << "ERROR: " << err << endl;
			cout << "Do you want to try database action again?" << endl;
			recover = decider();
		}
		catch (...) {
			cout << "Unknown Error. " << endl;
			cout << "Do you want to try database action again?" << endl;
			recover = decider();
		}
	}

	// Getting activityID
	int activityID = 0;
	while (true) {
		cout << left << std::setw(30) << "Activity ID *" << "\t: ";
		activityID = inputInt(false, true);

		// Return to menu if user entered "-1"
		if (activityID == -1) return;

		try {
			Session sess = getSessionDb();

			// Check if activity exists
			auto myRows2 = sess.sql("SELECT activityID FROM ACTIVITY WHERE activityID=?").bind(std::to_string(activityID)).execute();

			if (myRows2.count() == 0) {
				cout << "Activity does not exist. Do you want to add activity?" << endl;
				if (decider()) {
					activityAddEntry(userID);
					cout << "Please re-enter the activity ID." << endl;
					pause();
					continue;
				}
				else {
					return;

				}
			}
			else {
				break;

			}
		}
		catch (const mysqlx::Error& err)
		{
			cout << "ERROR: " << err << endl;
			cout << "Do you want to try database action again?" << endl;
			if (decider()) {
				continue;
			}
			else {
				return;
			}
		}
		catch (...) {
			cout << "Unknown Error. " << endl;
			cout << "Do you want to try database action again?" << endl;
			if (decider()) {
				continue;
			}
			else {
				return;
			}
		}
	}

	std::string preparedStatement1 = "INSERT INTO " + thisTableName + " (memberID, userID, activityID) VALUES (?, ?, ?)";

	recover = true;
	while (recover) {
		try {
			Session sess = getSessionDb();

			auto mySess = sess.sql(preparedStatement1);

			mySess = mySess
				.bind(std::to_string(memberID))
				.bind(std::to_string(userID))
				.bind(std::to_string(activityID));

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

void attendanceBatchAdd(int userID) {
	// Check if user wants to search for activity ID.
	while (true) {
		heading("ATTENDANCE > Batch Add Entry");
		printLine();

		cout << "Before adding data you may want to search for the activity ID. Do you want to do so?" << endl;
		if (decider()) {
			while (true) {
				heading("ATTENDANCE > Batch Add Entry > Search Selection");
				printLine();
				cout << "Enter \'1\' to list all entries, or \'2\' to fine tune your search. " << endl;
				int myInt = inputInt();

				// Return to menu if user entered "-1"
				if (myInt == -1) return;

				if (myInt == 1) {
					activityListEntries();
					break;
				}
				else if (myInt == 2) {
					activitySearchEntry();
					break;
				}
				else {
					cout << "Invalid option. Please re-input." << endl;
					pause();
				}

			}

		}
		else {
			break;
		}

	}

	heading("ATTENDANCE > Batch Add Entry > Obtaining Activity ID");
	printLine();


	// Getting activityID
	int activityID = 0;
	std::string activityName;
	while (true) {
		cout << left << std::setw(30) << "Activity ID *" << "\t: ";
		activityID = inputInt(false, true);

		// Return to menu if user entered "-1"
		if (activityID == -1) return;

		try {
			Session sess = getSessionDb();

			// Check if activity exists
			auto myRows2 = sess.sql("SELECT activityID FROM ACTIVITY WHERE activityID=?").bind(std::to_string(activityID)).execute();

			if (myRows2.count() == 0) {
				cout << "Activity does not exist. Do you want to re-input?" << endl;
				if (decider()) {
					continue;
				}
				else {
					return;

				}
			}
			else {
				break;

			}
		}
		catch (const mysqlx::Error& err)
		{
			cout << "ERROR: " << err << endl;
			cout << "Do you want to try database action again?" << endl;
			if (decider()) {
				continue;
			}
			else {
				return;
			}
		}
		catch (...) {
			cout << "Unknown Error. " << endl;
			cout << "Do you want to try database action again?" << endl;
			if (decider()) {
				continue;
			}
			else {
				return;
			}
		}
	}


	// Getting memberIDs
	std::vector<int> memberIDs;
	std::vector<std::string> matrixNos;
	while (true) {
		heading("ATTENDANCE > Batch Add Entry > Obtaining Activity ID > Obtaining Matrix Nos.");
		printLine();
		std::string matrixNo;
		cout << "Input matrix numbers of members, tapping \'Enter\' after each entry. \n- To stop input, enter '1234567'. \n- To delete 1 previous input, enter \'13555\'." << endl << endl;
		if (memberIDs.size() > 0) {
			cout << "Current inputs: " << endl;
			cout << matrixNos[0];
			for (int i = 1; i < memberIDs.size(); i++) {
				cout << ", " << matrixNos[i];
			}
			cout << endl;
		}

		cout << left << std::setw(30) << "Matrix No. *" << "\t: ";
		getline(cin, matrixNo);

		if (matrixNo == "1234567") {
			break;
		}
		else if (matrixNo == "13555") {
			matrixNos.pop_back();
			memberIDs.pop_back();
			continue;
		}
		else if (matrixNo == "-1") {
			return;
		}

		while (true) {
			try {
				Session sess = getSessionDb();

				cout << "Searching database for relevant Matrix No...\r";

				// Check if member exists
				auto myRows1 = sess.sql("SELECT * FROM MEMBER WHERE matrixNo=?").bind(matrixNo).execute();

				if (myRows1.count() == 0) {
					cout << "Member does not exist. Do you want to add member?" << endl;
					if (decider()) {
						memberAddEntry();
					}
					continue;

				}
				else {
					// Get memberID if exist
					auto myRows2 = sess.sql("SELECT memberID FROM MEMBER WHERE matrixNo=?").bind(matrixNo).execute();

					auto myRow2 = myRows2.fetchOne();

					std::stringstream ss1;
					myRow2.get(0).print(ss1);
					memberIDs.push_back(std::stoi(ss1.str()));
					matrixNos.push_back(matrixNo);

				}

			}
			catch (const mysqlx::Error& err)
			{
				cout << "ERROR: " << err << endl;
				cout << "Do you want to try database action again?" << endl;
				if (decider()) {
					continue;
				}
				else {
					return;
				}
			}
			catch (...) {
				cout << "Unknown Error. " << endl;
				cout << "Do you want to try database action again?" << endl;
				if (decider()) {
					continue;
				}
				else {
					return;
				}
			}
		}
	}


	std::string preparedStatement1 = "INSERT INTO " + thisTableName + " (memberID, userID, activityID) VALUES (?, ?, ?)";

	for (int i = 1; i < memberIDs.size(); i++) {
		preparedStatement1 += ", (?, ?, ?)";
	}


	while (true) {
		try {
			Session sess = getSessionDb();

			auto mySess = sess.sql(preparedStatement1);

			for (int i = 0; i < memberIDs.size(); i++) {
				mySess = mySess
					.bind(std::to_string(memberIDs[i]))
					.bind(std::to_string(userID))
					.bind(std::to_string(activityID));
			}

			auto myRows = mySess.execute();
			cout << "Adding into database...\r";

			if (myRows.getAffectedItemsCount() > 0) {
				cout << myRows.getAffectedItemsCount() << " rows added." << endl;
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
			if (decider()) {
				continue;
			}
			else {
				return;
			}
		}
		catch (...) {
			cout << "Unknown Error";
			cout << "Do you want to try database action again?" << endl;
			if (decider()) {
				continue;
			}
			else {
				return;
			}
		}

	}

	pause();
}

void attendanceSearchEntry() {
	// Copies searchable items to attendanceTempDataStore
	int tempCounter = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["searchable"]) {
			attendanceTempDataStore[tempCounter]["colName"] = attendanceDataStruct[i]["altColumnName"];
			attendanceTempDataStore[tempCounter]["colDesc"] = attendanceDataStruct[i]["columnDescription"];
			attendanceTempDataStore[tempCounter]["outputSizing"] = attendanceDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	// Copies orderable items to attendanceTempDataStore2
	tempCounter = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["orderable"]) {
			attendanceTempDataStore2[tempCounter]["colName"] = attendanceDataStruct[i]["altColumnName"];
			attendanceTempDataStore2[tempCounter]["colDesc"] = attendanceDataStruct[i]["columnDescription"];
			attendanceTempDataStore2[tempCounter]["outputSizing"] = attendanceDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	// Copies listable items to attendanceTempDataStore3
	tempCounter = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["selected"]) {
			attendanceTempDataStore3[tempCounter]["colName"] = attendanceDataStruct[i]["altColumnName"];
			attendanceTempDataStore3[tempCounter]["colDesc"] = attendanceDataStruct[i]["columnDescription"];
			attendanceTempDataStore3[tempCounter]["outputSizing"] = attendanceDataStruct[i]["outputSizing"];

			tempCounter++;
		}
	}

	std::string preparedStatement = "SELECT " + columnNamesGen(attendanceDataStruct, "selected", "altColumnName") + " FROM " + innerJoin + " WHERE ";

	int counter = 0;
	std::string criteriaStringUser = "Criteria: SELECT WHERE ";
	std::string criteriaStringSys = "";
	std::vector<std::string> criterias;

	do {
		if (counter > 0) {
			while (true) {
				heading("ATTENDANCE > Search > Criteria Generation > OR/AND Selection");
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

		heading("ATTENDANCE > Search > Criteria Generation > Column Selection");
		printLine();
		menuGen(attendanceTempDataStore, "colDesc");

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

				if (selection > attendanceTempDataStore.size() || selection < 0) {
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
		heading("ATTENDANCE > Search > Criteria Generation > Column Selection > Search Statement Generation");
		printLine();
		if (counter > 0) {
			cout << "\nCurrent " << criteriaStringUser << endl << endl;

		}
		cout << "Selected " << attendanceTempDataStore[selection]["colDesc"] << endl;

		// To get search criteria
		cout << "Please input the search criteria. You may use SQL-based wildcards like \"%\"\n\n> ";

		std::string criteria = "";
		std::getline(cin, criteria);

		// Return to menu if user entered "-1"
		if (criteria == "-1") return;

		criterias.push_back(criteria);
		criteriaStringUser += attendanceTempDataStore[selection]["colDesc"];
		criteriaStringUser += " is \"" + criteria + "\" \n";

		cout << "\n\n" << criteriaStringUser;


		criteriaStringSys += returnString(attendanceTempDataStore[selection]["colName"]) + " like ?";

		counter++;

		cout << "\nWould you like to add criteria? " << endl;

	} while (decider());


	int selection = 0;
	// Make and validate selection
	while (true) {
		heading("ACTIVITY > Search > Criteria Generation > Ordering Selection");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(attendanceTempDataStore2, "colDesc");
		selection = inputInt();
		// Return to menu if user entered "-1"
		if (selection == -1) return;
		if (selection < attendanceTempDataStore2.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	heading("ACTIVITY > Search > Result");
	printLine();
	cout << "Search statement " << criteriaStringUser << endl;

	preparedStatement += criteriaStringSys + " ORDER BY " + returnString(attendanceTempDataStore2[selection]["colName"]);


	// Print table headings
	int lineSize = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["selected"]) {
			cout << left << std::setw(attendanceDataStruct[i]["outputSizing"]) << returnString(attendanceDataStruct[i]["columnDescription"]);

			lineSize += attendanceDataStruct[i]["outputSizing"];

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
				cout << left << std::setw(attendanceTempDataStore3[i]["outputSizing"]) << row[i];
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

void attendanceDeleteEntry() {
	// To ask if the user wants to search for the relavant data
	while (true) {
		heading("ATTENDANCE > Delete Entry");
		printLine();
		cout << "Deleting will be based on attendance ID. Do you want to search attendance data?" << endl;

		if (!decider()) {
			break;
		}
		attendanceSearchEntry();
	}

	// Copy relavant data to attendanceTempDataStore
	int tempCounter = 0;
	for (int i = 0; i < attendanceDataStruct.size(); i++) {
		if (attendanceDataStruct[i]["showDuringDeletion"]) {
			attendanceTempDataStore[tempCounter]["colDesc"] = attendanceDataStruct[i]["columnDescription"];
			tempCounter++;
		}
	}

	int attendanceID;
	try {
		while (true) {
			heading("ATTENDANCE > Delete Entry > Data Collection");
			printLine();
			cout << "Please input member attendance ID to delete: ";
			attendanceID = inputInt(false, true);
			// Return to menu if user entered "-1"
			if (attendanceID == -1) return;

			std::string preparedStatement1 = "SELECT " + columnNamesGen(attendanceDataStruct, "showDuringDeletion", "altColumnName") + " FROM " + innerJoin + " WHERE a.attendanceID=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(std::to_string(attendanceID)).execute();

			printLine();

			// If there are no relavant rows, prompt the user to re-input
			if (myRows.count() > 0) {
				heading("ATTENDANCE > Delete Entry > Confirmation");
				printLine();
				cout << "Are you sure you want to delete the following entry?" << endl;
				for (Row row : myRows.fetchAll()) {
					for (int i = 0; i < row.colCount(); i++) {
						cout << left << std::setw(30) << returnString(attendanceTempDataStore[i]["colDesc"]) << "\t: ";
						cout << row[i] << endl;
					}
					cout << endl;
				}
				break;
			}
			else {
				cout << "No member with attendance ID " << attendanceID << " found." << endl;
				cout << "Try again?" << endl;
				if (decider()) {
					continue;
				}
				else {
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

	std::string preparedStatement2 = "DELETE FROM " + thisTableName + " WHERE attendanceID=?";

	if (decider()) {
		Session sess = getSessionDb();
		auto myRows = sess.sql(preparedStatement2).bind(std::to_string(attendanceID)).execute();

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
		heading("ATTENDANCE > Show Detail");
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
			heading("ATTENDANCE > Show Detail > Input Attendance ID");
			printLine();
			cout << "Please input Attendance ID to show: ";
			attendanceID = std::to_string(inputInt(false, true));

			// Return to menu if user entered "-1"
			if (attendanceID == "-1") return;

			std::string preparedStatement1 = "SELECT " + columnNamesGen(attendanceTempDataStore3, "showDuringDeletion", "colName") + " FROM " + innerJoin + " WHERE attendanceID=?";

			Session sess = getSessionDb();

			auto myRows = sess.sql(preparedStatement1).bind(attendanceID).execute();

			heading("ATTENDANCE > Show Detail > Results");
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
		heading("ATTENDANCE > Listing > Ordering");
		printLine();

		cout << "How would you like to order your results by?" << endl;
		menuGen(attendanceTempDataStore, "colDesc");
		selection = inputInt();
		// Return to menu if user entered "-1"
		if (selection == -1) return;

		if (selection < attendanceTempDataStore.size()) {
			break;
		}
		else {
			cout << "Please input a valid selection. " << endl;
			pause();
		}

	}

	heading("ATTENDANCE > Listing > Results");
	printLine();

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
			attendanceSearchEntry();
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
	}

	cout << endl;
	attendanceTempDataStore.clear();
	attendanceTempDataStore2.clear();
	attendanceTempDataStore3.clear();
	goto MenuStart;
}