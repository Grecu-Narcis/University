#pragma once
#include "Player.h"

#include <vector>
#include <stdexcept>

class Repository
{
private:
	vector<Player> playersList;

public:
	Repository();
	void addPlayer(Player playerToAdd);

	vector<Player> getAll();
};

