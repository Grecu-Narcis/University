#include "Service.h"

#include <algorithm>

Service::Service(Repository& playersRepository) : playersRepository(playersRepository)
{
}

void Service::addPlayer(string name, string nationality, string playingTeam, int numberOfGoals)
{
	/*
	* Creates a player with given arguments and add it to repository.
	* 
	* <param name> string, the name of the player
	* <param nationality> string, the nationality of the player
	* <param playingTeam> string, the team for which player is playing	
	* <param numberOfGoals> int, the number of goals scored by the player
	*/

	Player playerToAdd(name, nationality, playingTeam, numberOfGoals);

	playersRepository.addPlayer(playerToAdd);
}

vector<Player> Service::getAll()
{
	return playersRepository.getAll();
}

vector<Player> Service::getPlayersFromTeam(string teamToSearch)
{
	/*
	* Retrieves all players that plays for `teamToSearch` sorted in ascending order by goals.
	* 
	* <param teamToSearch> string, representing the team for which we are looking for
	* 
	* Return: vector<Player> representing the list of players with the given team.
	*/

	vector<Player> playersFromTeam;

	for (auto player : getAll())
		if (player.getPlayingTeam() == teamToSearch)
			playersFromTeam.push_back(player);

	sort(playersFromTeam.begin(), playersFromTeam.end(),
		[](Player firstPlayer, Player secondPlayer)
		{ return firstPlayer.getNumberOfGoals() < secondPlayer.getNumberOfGoals(); });

	return playersFromTeam;
}

int Service::getNumberOfGoalsForTeam(string teamToSearch)
{
	int result = 0;

	for (auto player : getAll())
		if (player.getPlayingTeam() == teamToSearch)
			result += player.getNumberOfGoals();

	return result;
}
