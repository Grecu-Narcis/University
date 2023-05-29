#include "AppUI.h"

#include <iostream>
#include <Windows.h>

#include <shellapi.h>

using std::cout;
using std::cin;
using std::endl;
using std::getline;


void AppUI::changeConsoleColor(int newConsoleColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(hConsole, newConsoleColor);
}


void AppUI::printMessageInGreen(string messageToPrint)
{
	this->changeConsoleColor(FOREGROUND_GREEN);
	cout << messageToPrint << "\n\n";
	this->changeConsoleColor(15);
}


void AppUI::printMessageInRed(string messageToPrint)
{
	this->changeConsoleColor(FOREGROUND_RED);
	cout << messageToPrint << "\n\n";
	this->changeConsoleColor(15);
}


AppUI::AppUI(AdministratorService& workingAdminService, UserService& workingUserService) : 
	adminService(workingAdminService), userService(workingUserService)
{
}

void AppUI::mainMenu()
{
	cout << "Hello and welcome to Master C++!\n";

	string userOption = "";

	while (true)
	{
		cout << "\nType:\nadmin - for admin mode\nuser - for user mode\nexit - to end the program\nYour option: ";

		getline(cin, userOption);

		if (userOption == "user")
			this->userMenu();

		else if (userOption == "admin")
			this->adminMenu();

		else if (userOption == "exit")
		{
			cout << "Hope we'll meet again!\n";
			break;
		}
		
		else
		{
			this->changeConsoleColor(FOREGROUND_RED);

			cout << "Please enter a valid mode (admin/user)!\n\n";

			this->changeConsoleColor(15);
		}
	}
}


void AppUI::printAdminMenu()
{
	cout << "Press:\n";
	cout << "1 - to add a new tutorial.\n";
	cout << "2 - to update a tutorial.\n";
	cout << "3 - to delete a tutorial.\n";
	cout << "4 - to print all tutorials.\n";
	cout << "5 - for main menu.\n";
}


void AppUI::adminAddTutorialMenu()
{
	string tutorialTitle, tutorialPresenter, tutorialLink;
	int tutorialNumberOfLikes;
	Duration tutorialDuration;

	cout << "Enter tutorial title: ";
	getline(cin, tutorialTitle);

	cout << "Enter tutorial presenter: ";
	getline(cin, tutorialPresenter);

	cout << "Enter tutorial link: ";
	getline(cin, tutorialLink);

	cout << "Enter number of likes: ";
	cin >> tutorialNumberOfLikes;

	cout << "Enter tutorial duration (minutes seconds): ";
	cin >> tutorialDuration.minutes >> tutorialDuration.seconds;

	int result = getchar();

	try
	{
		this->adminService.addTutorial(tutorialTitle, tutorialPresenter, tutorialLink, 
			tutorialNumberOfLikes, tutorialDuration.minutes, tutorialDuration.seconds);

		this->changeConsoleColor(FOREGROUND_GREEN);

		cout << "[+] Tutorial added successfully!\n\n";
		
		this->changeConsoleColor(15);
	}

	catch (std::exception& thrownException)
	{
		this->changeConsoleColor(FOREGROUND_RED);

		cout << "[!] " << thrownException.what() << "\n\n";

		this->changeConsoleColor(15);
	}
}


void AppUI::adminUpdateTutorialMenu()
{
	string tutorialTitle, tutorialPresenter, tutorialLink;
	int tutorialNumberOfLikes;
	Duration tutorialDuration;

	cout << "Enter tutorial title: ";
	getline(cin, tutorialTitle);

	cout << "Enter tutorial presenter: ";
	getline(cin, tutorialPresenter);

	cout << "Enter tutorial link: ";
	getline(cin, tutorialLink);

	cout << "Enter number of likes: ";
	cin >> tutorialNumberOfLikes;

	cout << "Enter tutorial duration (minutes seconds): ";
	cin >> tutorialDuration.minutes >> tutorialDuration.seconds;

	int result = getchar();

	try
	{
		this->adminService.updateTutorial(tutorialTitle, tutorialPresenter, tutorialLink, \
			tutorialNumberOfLikes, tutorialDuration.minutes, tutorialDuration.seconds);

		this->changeConsoleColor(FOREGROUND_GREEN);

		cout << "[+] Tutorial updated successfully!\n\n";

		this->changeConsoleColor(15);
	}

	catch (std::exception& thrownException)
	{
		this->changeConsoleColor(FOREGROUND_RED);

		cout << "[!] " << thrownException.what() << "\n\n";

		this->changeConsoleColor(15);
	}
}


void AppUI::adminDeleteTutorialMenu()
{
	string tutorialTitle, tutorialPresenter;

	cout << "Enter tutorial title: ";
	getline(cin, tutorialTitle);

	cout << "Enter tutorial presenter: ";
	getline(cin, tutorialPresenter);

	try
	{
		this->adminService.deleteTutorial(tutorialTitle, tutorialPresenter);

		this->changeConsoleColor(FOREGROUND_GREEN);

		cout << "[+] Tutorial deleted successfully!\n\n";

		this->changeConsoleColor(15);
	}

	catch (std::exception& thrownException)
	{
		this->changeConsoleColor(FOREGROUND_RED);

		cout << "[!] " << thrownException.what() << "\n\n";

		this->changeConsoleColor(15);
	}
}


void AppUI::adminMenu()
{
	while (true)
	{
		this->printAdminMenu();

		cout << "Your option is: ";

		string option;
		getline(cin, option);

		if (option == "1")
		{
			this->adminAddTutorialMenu();
		}

		else if (option == "2")
		{
			this->adminUpdateTutorialMenu();
		}

		else if (option == "3")
		{
			this->adminDeleteTutorialMenu();
		}

		else if (option == "4")
		{
			this->printAllTutorials();
		}

		else if (option == "5")
			break;

		else
		{
			this->changeConsoleColor(FOREGROUND_RED);

			cout << "Invalid option!\n\n";
	
			this->changeConsoleColor(15);
		}
	}
}


void AppUI::printTutorial(Tutorial tutorialToPrint)
{
	cout << "\n";
	cout << "Tutorial title: " << tutorialToPrint.getTitle() << "\n";
	cout << "Tutorial presenter: " << tutorialToPrint.getPresenter() << "\n";
	cout << "Tutorial link: " << tutorialToPrint.getLink() << "\n";
	cout << "Tutorial number of likes: " << tutorialToPrint.getNumberOfLikes() << "\n";
	cout << "Tutorial duration in minutes and seconds: " << tutorialToPrint.getDuration().minutes \
		 << " minutes and " << tutorialToPrint.getDuration().seconds << " seconds\n\n";
}


void AppUI::printAllTutorials()
{
	vector<Tutorial> allTutorials = this->adminService.getAllTutorials();

	if (allTutorials.size() == 0)
	{
		cout << "There are no tutorials available!\n\n";
		return;
	}

	cout << "Available tutorials are: \n\n";

	for (auto tutorial : allTutorials)
		this->printTutorial(tutorial);

	cout << "\n";
}


void AppUI::printUserMenu()
{
	cout << "\nPress:\n";
	cout << "1 - to see the tutorials with a specific presenter.\n";
	cout << "2 - to delete a tutorial from watch list.\n";
	cout << "3 - to see the watch list.\n";
	cout << "4 - to exit.\n";
}


void AppUI::userAllTutorialsWithGivenPresenterMenu()
{
	string requiredPresenter;

	cout << "Enter the presenter you want to look for (empty string for all presenters): ";
	getline(cin, requiredPresenter);

	vector<Tutorial> tutorialsWithPresenter = this->userService.getTutorialsWithPresenter(requiredPresenter);

	if (tutorialsWithPresenter.size() == 0)
	{
		cout << "There are no tutorials with the required presenter!\n\n";
		return;
	}

	if (requiredPresenter != "")
		cout << "Tutorials presented by " << requiredPresenter << " are: \n";
	else
		cout << "Here are all the tutorials:\n";

	int tutorialIndex = 0;

	while (true)
	{
		cout << "Current tutorial is: \n";
		this->printTutorial(tutorialsWithPresenter[tutorialIndex]);

		string userOption;

		while (true)
		{
			cout << "Type add to add the tutorial in the watch list.\n";
			cout << "Type next to see the next tutorial.\n";
			cout << "Type stop to stop tutorials presentation.\n";

			cout << "Your option: ";
			getline(cin, userOption);

			if (userOption == "add")
			{
				try
				{
					this->userService.addTutorialToWatchList(tutorialsWithPresenter[tutorialIndex]);
					this->printMessageInGreen("[+] Tutorial added successfully to watch list!");
				}
				catch (std::exception& thrownException)
				{
					this->printMessageInRed(string("[!] Tutorial already in watch list!"));
				}
			}

			else if (userOption == "next")
				break;

			else if (userOption == "stop")
				return;

			else
				cout << "Invalid command!\n";
		}

		tutorialIndex = (tutorialIndex + 1) % tutorialsWithPresenter.size();
	}
}


void AppUI::userDeleteTutorialMenu()
{
	string tutorialTitle, tutorialPresenter, userLikeAnswer;

	cout << "Enter title of the tutorial you want to delete: ";
	getline(cin, tutorialTitle);

	cout << "Enter presenter of the tutorial you want to delete: ";
	getline(cin, tutorialPresenter);

	cout << "Do you like the tutorial? (yes/no): ";
	getline(cin, userLikeAnswer);

	bool tutorialIsLiked = false;

	if (userLikeAnswer == "yes")
		tutorialIsLiked = true;
	
	try
	{
		this->userService.deleteTutorialFromWatchList(tutorialTitle, tutorialPresenter, tutorialIsLiked);
		this->printMessageInGreen("[+] Tutorial was deleted successfully!");
	}

	catch (std::exception& e)
	{
		this->printMessageInRed("[!] " + string(e.what()));
	}
}


void AppUI::userPrintWatchList()
{
	vector<Tutorial> watchList = this->userService.getWatchList();

	if (watchList.size() == 0)
	{
		cout << "\nThere are no tutorials in the watch list :(\n\n";
		return;
	}

	cout << "\nTutorials in the watch list are: \n";

	for (auto& tutorial : watchList)
		this->printTutorial(tutorial);
}


void AppUI::userMenu()
{
	while (true)
	{
		this->printUserMenu();

		string userOption;

		cout << "Your option is: ";
		getline(cin, userOption);

		if (userOption == "1")
		{
			this->userAllTutorialsWithGivenPresenterMenu();
		}

		else if (userOption == "2")
		{
			this->userDeleteTutorialMenu();
		}

		else if (userOption == "3")
		{
			this->userService.openWatchList();
		}

		else if (userOption == "4")
			break;

		else
		{
			cout << "Invalid option!\n";
		}
	}
}


