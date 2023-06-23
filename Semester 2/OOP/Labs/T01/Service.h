#pragma once

#include "Repository.h"
#include "Player.h"

class Service
{
private:
	Repository& playersRepository;

public:
	Service(Repository& playersRepository);
	void addPlayer(string name, string nationality, string playingTeam, int numberOfGoals);

	vector<Player> getAll();

	vector<Player> getPlayersFromTeam(string teamToSearch);
	int getNumberOfGoalsForTeam(string teamToSearch);
};

