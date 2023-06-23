#pragma once
#include <string>

using namespace std;

class Player
{
private:
	string name, nationality, playingTeam;
	int numberOfGoals;

public:
	Player(string name, string nationality, string playingTeam, int numberOfGoals);
	
	string getName();
	string getNationality();
	string getPlayingTeam();
	int getNumberOfGoals();
};

