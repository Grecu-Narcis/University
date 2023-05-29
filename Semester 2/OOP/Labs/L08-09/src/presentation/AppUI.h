#ifndef __APP_UI_H__
#define __APP_UI_H__

#include <string>

#include "../business/AdministratorService.h"
#include "../business/UserService.h"
#include "../domain/Tutorial.h"

using std::string;

class AppUI
{
private:
	string appMode;
	AdministratorService& adminService;
	UserService& userService;

	void changeConsoleColor(int newConsoleColor);
	void printMessageInGreen(string messageToPrint);
	void printMessageInRed(string messageToPrint);


public:
	AppUI(AdministratorService& workingAdminService, UserService& workingUserService);

	void mainMenu();

	void adminMenu();
	void printAdminMenu();

	void adminAddTutorialMenu();
	void adminUpdateTutorialMenu();
	void adminDeleteTutorialMenu();

	void printTutorial(Tutorial tutorialToPrint);
	void printAllTutorials();

	void userMenu();
	void printUserMenu();

	void userAllTutorialsWithGivenPresenterMenu();
	void userDeleteTutorialMenu();
	void userPrintWatchList();
};

#endif