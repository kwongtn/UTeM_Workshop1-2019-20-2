#include "utils.h"

using namespace ::mysqlx;

Session getSessionDb();

void superUser() {
	while (true) {
		std::string statement = "";

		// Get database statement to be executed.
		heading("Super User Mode. \nAny action done here will directly affect database. Use carefully.");
		printLine();

		cout << "> ";
		getline(cin, statement, ';');
		cin.ignore();

		heading("Super User Mode. \nAny action done here will directly affect database. Use carefully.");
		printLine();
		cout << "Are you sure you want to execute the following statement? " << endl;
		cout << "> " << statement << endl;

		if (decider()) {
			try {
				auto db = getSessionDb();

				auto myResult = db.sql(statement).execute();

				cout << "\n\nStatement executed. " << endl << endl;

				try {
					myResult.getAffectedItemsCount();
					cout << left << std::setw(30) << "Rows affected" << ": " << myResult.getAffectedItemsCount() << endl;
				} catch (...) {}

				try {
					myResult.count();
					cout << left << std::setw(30) << "Rows returned" << ": " << myResult.count() << endl;
				} catch (...){}

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


		}
		cout << "\n\nExit to main menu?" << endl;
		if (decider()) {
			return;
		}

	}

}