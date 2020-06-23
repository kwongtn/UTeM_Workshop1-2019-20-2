#include "utils.h"

using namespace ::mysqlx;

Session getSessionDb();

void superUser() {
	while (true) {
		std::string statement = "";

		// Get database statement to be executed.
		heading("Super User Mode. \nAny action done here will directly affect database. Use carefully. \nEnter \'exit;\' to exit superuser mode and \'clear\' to clear screen.");
		printLine();

		while (true) {

			cout << "> ";
			getline(cin, statement, ';');
			cin.ignore();

			if (statement == "exit") {
				return;
			}
			else if (statement == "clear") {
				break;
			}

			try {
				auto db = getSessionDb();

				auto myResult = db.sql(statement).execute();

				cout << "\n\nStatement executed. " << endl << endl;

				try {
					myResult.getAffectedItemsCount();
					cout << left << std::setw(30) << "Rows affected" << ": " << myResult.getAffectedItemsCount() << endl;
				}
				catch (...) {}

				try {
					myResult.getWarningsCount();
					cout << left << std::setw(30) << "Warnings" << ": " << myResult.getWarningsCount() << endl;
				}
				catch (...) {}

				try {
					myResult.count();
					cout << left << std::setw(30) << "Rows returned" << ": " << myResult.count() << endl << endl << endl;

					if (myResult.count() > 0) {
						for (int i = 0; i < myResult.getColumnCount(); i++) {
							cout << myResult.getColumn(i) << "\t";
						}
						cout << endl;
						printLine();

						for (Row row : myResult.fetchAll()) {
							for (int i = 0; i < row.colCount(); i++) {
								cout << row[i] << "\t";
							}
							cout << endl;
						}
					}
				}
				catch (...) {}

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

			cout << endl;


		}

	}

}