#include "Repository.h"

Repository::Repository()
{
	Player player1("Nora Mork", "NOR", "Larvik", 83);
	Player player2("Cristina Neagu", "ROU", "Buducnost", 63);
	Player player3("Ilina Ekaterina", "RUS", "Rostov-Don", 80);
	Player player4("Allison Pineau", "ROU", "Buducnost", 64);
	Player player5("Selena Gomez", "RUS", "Buducnost", 52);

	addPlayer(player1);
	addPlayer(player2);
	addPlayer(player3);
	addPlayer(player4);
	addPlayer(player5);
}

void Repository::addPlayer(Player playerToAdd)
{
	/*
	* Adds a new player to repository. 
	* If the player already exists, it throws an exception.
	* 
	* <param playerToAdd> Player, representing the player we try to add.
	*/

	for (auto player : playersList)
		if (player.getName() == playerToAdd.getName())
			throw exception("Player already in list!");

	playersList.push_back(playerToAdd);
}

vector<Player> Repository::getAll()
{
	return playersList;
}
