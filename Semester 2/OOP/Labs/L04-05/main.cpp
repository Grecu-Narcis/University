#include "DynamicArray.h"
#include "Testing.h"

#include "AppUI.h"
#include "AdministratorService.h"
#include "UserService.h"

#include <iostream>
#include <crtdbg.h>


int main()
{
	{
		Testing test;

		test.testAll();


		std::cout << "\n\n";

		TutorialsRepository tutorialsDatabase;
		tutorialsDatabase.addSampleData();
		AdministratorService adminTutorialService(tutorialsDatabase);
		UserService userTutorialService(tutorialsDatabase);
		AppUI ui(adminTutorialService, userTutorialService);

		ui.mainMenu();
	}

	_CrtDumpMemoryLeaks();

	system("pause");
}