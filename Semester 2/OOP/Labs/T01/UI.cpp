#include "UI.h"

#include <iostream>

using namespace std;

UI::UI(Service& playersService) : playersService(playersService)
{
}

void UI::printMenu()
{
	cout << "Press 1 to add a new player\n";
	cout << "Press 2 to show all the players.\n";
	cout << "Press 3 to sort the players that play for a given team by the number of goals.\n";
	cout << "Press 4 to exit.\n";
}

void UI::mainMenu()
{
	string userOption;

	while (true)
	{
		printMenu();

		cout << "Your option is: ";
		getline(cin, userOption);

		cout << '\n';

		if (userOption == "1")
		{
			addPlayerMenu();
		}

		else if (userOption == "2")
		{
			vector<Player> players = playersService.getAll();

			cout << "Players are: \n";

			for (auto player : players)
			{
				cout << player.getName() << " | " << player.getNationality() << " | ";
				cout << player.getPlayingTeam() << " | " << player.getNumberOfGoals() << "\n";
			}

		}

		else if (userOption == "3")
		{
			string requiredTeam;
			cout << "Enter the team you want to search for: ";
			getline(cin, requiredTeam);

			vector<Player> players = playersService.getPlayersFromTeam(requiredTeam);

			if (players.size() == 0)
			{
				cout << "No players with required team.\n\n";
				continue;
			}

			cout << "Players are: \n";

			for (auto player : players)
			{
				cout << player.getName() << " | " << player.getNationality() << " | ";
				cout << player.getPlayingTeam() << " | " << player.getNumberOfGoals() << "\n";
			}

			cout << "Total number of goals is: " << playersService.getNumberOfGoalsForTeam(requiredTeam) << '\n';
		}

		else if (userOption == "4")
			break;

		else
		{
			cout << "Invalid command!\n";
		}

		cout << '\n';
	}
}

void UI::addPlayerMenu()
{
	string name, nationality, playingTeam, numberOfGoalsAsString;
	int numberOfGoals;

	cout << "Enter name of the player: ";
	getline(cin, name);

	cout << "Enter nationality of the player: ";
	getline(cin, nationality);

	cout << "Enter the team for which is playing: ";
	getline(cin, playingTeam);

	cout << "Enter the number of goals scored: ";
	getline(cin, numberOfGoalsAsString);

	numberOfGoals = stoi(numberOfGoalsAsString);

	try
	{
		playersService.addPlayer(name, nationality, playingTeam, numberOfGoals);
		cout << "Player addded successfully!\n";
	}

	catch (exception& e)
	{
		cout << e.what() << '\n';
	}
}
