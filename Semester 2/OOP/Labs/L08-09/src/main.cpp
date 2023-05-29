#include "infrastructure/FileRepository.h"
#include "business/UserService.h"
#include "business/AdministratorService.h"
#include "presentation/AppUI.h"
#include "testing/Testing.h"
#include "business/CSVWatchList.h"
#include "business/HTMLWatchList.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel.h>
#include <QtWidgets>
#include "presentation/AppGUI.h"

int main(int argc, char** argv)
{
	// Testing::testAll();

	QApplication app(argc, argv);

	FileRepository tutorialDatabase{ "demo.txt" };

	FileWatchList* watchList = nullptr;
	watchList = new HTMLWatchList{ "watchlist.html" };
	AdministratorService adminService{ tutorialDatabase };
	UserService userService{ tutorialDatabase, watchList };


	AppGUI demo{ adminService, userService };

	demo.resize(600, 400);
	demo.show();

	return app.exec();
}