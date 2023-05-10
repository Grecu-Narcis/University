#include "Player.h"

Player::Player(string name, string nationality, string playingTeam, int numberOfGoals) : 
	name(name), nationality(nationality), playingTeam(playingTeam), numberOfGoals(numberOfGoals)
{
}

string Player::getName()
{
	return name;
}

string Player::getNationality()
{
	return nationality;
}

string Player::getPlayingTeam()
{
	return playingTeam;
}

int Player::getNumberOfGoals()
{
	return numberOfGoals;
}
