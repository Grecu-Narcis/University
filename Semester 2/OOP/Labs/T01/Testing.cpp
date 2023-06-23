#include "Testing.h"

#include <assert.h>
#include <iostream>

using namespace std;

void testAddPlayerRepo()
{
	string name = "Test", nationality = "Demo", team = "aaa";
	int numberOfGoals = 23;

	Player p1(name, nationality, team, numberOfGoals);

	Repository testRepository;

	// test add - repo
	testRepository.addPlayer(p1);
	vector<Player> playersList = testRepository.getAll();

	assert(playersList.size() == 6);

	assert(playersList[5].getName() == "Test");
	assert(playersList[5].getNationality() == "Demo");
	assert(playersList[5].getPlayingTeam() == "aaa");
	assert(playersList[5].getNumberOfGoals() == 23);

	try 
	{
		testRepository.addPlayer(p1);
		assert(false);
	}

	catch (exception& e)
	{
		assert(true);
	}
}

void testAddPlayerService()
{
	string name = "Test", nationality = "Demo", team = "aaa";
	int numberOfGoals = 23;

	Player p1(name, nationality, team, numberOfGoals);

	Repository testRepository;
	Service testService(testRepository);


	// test add - repo
	testService.addPlayer(name, nationality, team, numberOfGoals);
	vector<Player> playersList = testService.getAll();

	assert(playersList[5].getName() == "Test");
	assert(playersList[5].getNationality() == "Demo");
	assert(playersList[5].getPlayingTeam() == "aaa");
	assert(playersList[5].getNumberOfGoals() == 23);

	try
	{
		testService.addPlayer(name, nationality, team, numberOfGoals);
		assert(false);
	}

	catch (exception& e)
	{
		assert(true);
	}

}

void testGetPlayersFromTeam()
{
	Repository testRepo;
	Service testService(testRepo);

	testService.addPlayer("Demo", "Demo", "Buducnost", 100);

	vector<Player> playersFromTeam = testService.getPlayersFromTeam("Buducnost");

	assert(playersFromTeam.size() == 4);

	for (int i = 0; i < playersFromTeam.size() - 1; i++)
		assert(playersFromTeam[i].getNumberOfGoals() <= playersFromTeam[i + 1].getNumberOfGoals());
}

void runAllTests()
{
	testAddPlayerRepo();
	testAddPlayerService();
	testGetPlayersFromTeam();

	cout << "All tests passed!\n";
}
