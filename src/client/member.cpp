#include "utils.h"

using namespace ::mysqlx;

// Define external functions
Session getSessionDb();
std::string columnNamesGen(json);
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

json memberDb{
	{
		{"columnName", "memberID"},
		{"columnDescription", "Member ID"},
	 	{"selected", false}
	},
	{
		{"columnName", "engName"},
		{"columnDescription", "English Name"},
	 	{"selected", true}
	},
	{
		{"columnName", "matrixNo"},
		{"columnDescription", "Matrix No"},
	 	{"selected", true}
	},
	{
		{"columnName", "icNo"},
		{"columnDescription", "IC No"},
	 	{"selected", true}
	},
	{
		{"columnName", "email"},
		{"columnDescription", "E-Mail"},
	 	{"selected", false}
	},
	{
		{"columnName", "phoneNo"},
		{"columnDescription", "Phone No"},
	 	{"selected", false}
	},
	{
		{"columnName", "facebookID"},
		{"columnDescription", "Facebook ID"},
	 	{"selected", false}
	},
	{
		{"columnName", "hostel"},
		{"columnDescription", "Hostel"},
	 	{"selected", false}
	},
	{
		{"columnName", "signupTime"},
		{"columnDescription", "Signup Time"},
	 	{"selected", false}
	},
	{
		{"columnName", "updateTime"},
		{"columnDescription", "Update Time"},
	 	{"selected", false}
	}
};

// Search entry


// Create entry


// List entry
void listEntries() {

	try {
		Session sess = getSessionDb();

		std::string selection = columnNamesGen(memberDb);

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

}

// Update entry


// Delete entry




void memberMenu() {
	unsigned short int selection = 0;

MenuStart:
	json menuEntries = { "Add Member", "List Members", "Update Member", "Delete Member" };

	clearScreen();

	heading();
	cout << "MEMBER" << endl;

	printLine();


	for (int i = 0; i < menuEntries.size(); i++) {
		cout << left << i + 1 << "\t" << returnString(menuEntries[i]) << endl;
	}
	cout << left << 10 << "\t" << "Exit" << endl;
	cout << menuEntries.size();


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

			break;
		case 2:
			listEntries();
			break;
		case 3:
			//TODO: Attendance Menu
			break;
		case 4:

			break;
		case 5:

			break;
		case 10:
			exit(0);
			break;
		default:
			cout << "Default pathway";
			throw "Invalid Selection";
			break;
		}
	}
	catch (...) {
		cout << "\nPlease input a valid selection. \n";
		cin.clear();
	}

	cout << endl;
	system("pause");
	goto MenuStart;
}