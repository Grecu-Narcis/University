#include "Testing.h"
#include "../domain/Tutorial.h"
#include "../infrastructure/MemoryRepository.h"
#include "../infrastructure/RepositoryException.h"
#include "../business/AdministratorService.h"
#include "../business/UserService.h"
#include "../business/CSVWatchList.h"

#include <cassert>
#include <stdexcept>
#include "../domain/TutorialValidator.h"
#include "../domain/ValidatorException.h"
#include "../infrastructure/FakeRepository.h"


void Testing::testDuration()
{
	Duration testDuration;
	Duration testDuration1(2, 4);

	assert(testDuration.minutes == 0);
	assert(testDuration.seconds == 0);

	assert(testDuration1.minutes == 2);
	assert(testDuration1.seconds == 4);

	assert(testDuration1.toString() == "2,4");
}


void Testing::testTutorialToString()
{
	Duration testDuration(5, 23);

	Tutorial testTutorial("c++", "john smith", "www.google.com", 4, testDuration);

	assert(testTutorial.toString() == "c++,john smith,www.google.com,4,5,23\n");
}


void Testing::testTutorialIsNull()
{
	Duration testDuration(5, 23);
	Tutorial testTutorial("c++", "john smith", "www.google.com", 4, testDuration);
	assert(testTutorial.isNull() == false);

	testTutorial.setTitle("");
	assert(testTutorial.isNull() == false);

	testTutorial.setPresenter("");
	assert(testTutorial.isNull() == false);

	testTutorial.setLink("");
	assert(testTutorial.isNull() == false);

	testTutorial.setNumberOfLikes(-1);
	assert(testTutorial.isNull() == false);

	testTutorial.setDuration(Duration(-1, 0));
	assert(testTutorial.isNull() == false);

	testTutorial.setDuration(Duration(-1, -1));
	assert(testTutorial.isNull() == true);
}


void Testing::testTutorial()
{
	testTutorialToString();
	testTutorialIsNull();

	Duration testDuration(5, 23);

	Tutorial testTutorial("c++", "john smith", "www.google.com", 4, testDuration);

	assert(testTutorial.getTitle() == "c++");
	assert(testTutorial.getPresenter() == "john smith");
	assert(testTutorial.getLink() == "www.google.com");
	assert(testTutorial.getNumberOfLikes() == 4);
	assert(testTutorial.getDuration().minutes == 5);
	assert(testTutorial.getDuration().seconds == 23);

	testDuration.minutes = 0;

	testTutorial.setTitle("random title");
	testTutorial.setPresenter("random presenter");
	testTutorial.setNumberOfLikes(100);
	testTutorial.setDuration(testDuration);

	assert(testTutorial.getTitle() == "random title");
	assert(testTutorial.getPresenter() == "random presenter");
	assert(testTutorial.getNumberOfLikes() == 100);
	assert(testTutorial.getDuration().minutes == 0);
	assert(testTutorial.getDuration().seconds == 23);
}


void Testing::testTutorialValidator()
{
	ValidatorException exceptionToTestWhat("test");

	assert(string(exceptionToTestWhat.what()) == "test");

	Duration testDuration(-1, -1);
	Tutorial testTutorial("", "jt", "", -1, testDuration);

	try
	{
		TutorialValidator::validate(testTutorial);
		assert(false);
	}

	catch (ValidatorException& e)
	{
		assert(true);
	}
}


void Testing::testRepository()
{
	MemoryRepository testRepo;

	assert(testRepo.getSize() == 0);

	Duration testDuration(5, 23);

	Tutorial testTutorial("c++", "john smith", "www.google.com", 4, testDuration);

	// test add
	testRepo.addTutorial(testTutorial);

	assert(testRepo.getSize() == 1);
	assert(testRepo.findPosition("c++", "john smith") == 0);

	try
	{
		testRepo.addTutorial(testTutorial);
		assert(false);
	}

	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial already in repository!");
	}

	// test update
	Tutorial testTutorial2(testTutorial);
	testTutorial2.setLink("new link");
	testRepo.updateTutorial(testTutorial2);

	assert(testRepo.getTutorialAtIndex(0).getLink() == "new link");

	try
	{
		Tutorial testTutorial3(testTutorial);
		testTutorial3.setTitle("random title");

		testRepo.updateTutorial(testTutorial3);
		
		assert(false);
	}

	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial not in repository!");
	}

	// test delete
	testRepo.deleteTutorial(testTutorial.getTitle(), testTutorial.getPresenter());
	assert(testRepo.getSize() == 0);

	try
	{
		testRepo.deleteTutorial("random title", "random presenter");
		assert(false);
	}

	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial not in repository!");
	}

	// test getTutorialAtIndex
	testRepo.addTutorial(testTutorial);
	Tutorial result = testRepo.getTutorialAtIndex(0);

	assert(result == testTutorial);

	try
	{
		testRepo.getTutorialAtIndex(-1);
		assert(false);
	}
	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Index out of range! - Repository");
	}

	try
	{
		testRepo.getTutorialAtIndex(7);
		assert(false);
	}
	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Index out of range! - Repository");
	}
}

void Testing::testAdministratorService()
{
	MemoryRepository testRepo;
	AdministratorService testService(testRepo);
	vector<Tutorial> allTutorials;

	Tutorial testTutorial("test title", "test presenter", "test link", 5, Duration(5, 23));

	// test add
	testService.addTutorial("test title", "test presenter", "test link", 5, 5, 23);
	allTutorials = testService.getAllTutorials();
	
	assert(allTutorials.size() == 1);
	assert(allTutorials[0] == testTutorial);

	// test add Exception

	try
	{
		testService.addTutorial("test title", "test presenter", "test link", 5, 5, 23);
		assert(false);
	}

	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial already in repository!");
	}


	// test update
	// Tutorial testTutorial2("test title", "test presenter", "test link", 6, Duration(5, 23));
	testService.updateTutorial("test title", "test presenter", "test link", 6, 5, 23);
	allTutorials = testService.getAllTutorials();

	assert(allTutorials.size() == 1);
	assert(allTutorials[0].getNumberOfLikes() == 6);

	// test update exception

	try
	{
		testService.updateTutorial("random title", "test presenter", "test link", 6, 5, 23);
		assert(false);
	}

	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial not in repository!");
	}

	
	// test delete

	testService.deleteTutorial("test title", "test presenter");
	allTutorials = testService.getAllTutorials();

	assert(allTutorials.size() == 0);

	try
	{
		testService.deleteTutorial("test title", "test presenter");
		assert(false);
	}

	catch (RepositoryException& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial not in repository!");
	}
}

void Testing::testUserService()
{
	MemoryRepository testTutorialsRepo;
	testTutorialsRepo.addSampleData();

	FileWatchList* testWatchList = new CSVWatchList{ "test-csv.csv" };

	UserService userTestService(testTutorialsRepo, testWatchList);

	// test getTutorialsWithPresenter 
	vector<Tutorial> tutorialsWithPresenter = userTestService.getTutorialsWithPresenter("nothing");

	assert(tutorialsWithPresenter.size() == 0);

	tutorialsWithPresenter = userTestService.getTutorialsWithPresenter("Bocicor Iuliana");
	assert(tutorialsWithPresenter.size() == 1);
	assert(tutorialsWithPresenter[0].getTitle() == string("Advanced C++"));
	assert(tutorialsWithPresenter[0].getPresenter() == string("Bocicor Iuliana"));
	assert(tutorialsWithPresenter[0].getLink() == string("https://www.cs.ubbcluj.ro"));
	assert(tutorialsWithPresenter[0].getNumberOfLikes() == 15240);
	assert(tutorialsWithPresenter[0].getDuration().minutes == 90);
	assert(tutorialsWithPresenter[0].getDuration().seconds == 15);

	tutorialsWithPresenter = userTestService.getTutorialsWithPresenter("");
	assert(tutorialsWithPresenter.size() == 10);
	

	// test addTutorialToWatchList and getWatchList
	vector<Tutorial> tutorialsWatchList = userTestService.getWatchList();
	vector<Tutorial> tutorialsDatabase = userTestService.getAllTutorialsFromDatabase();

	assert(tutorialsWatchList.size() == 0);
	
	userTestService.addTutorialToWatchList(tutorialsDatabase[0]);


	tutorialsWatchList = userTestService.getWatchList();

	assert(tutorialsWatchList.size() == 1);
	assert(tutorialsWatchList[0] == tutorialsDatabase[0]);
	assert(tutorialsWatchList[0].getLink() == tutorialsDatabase[0].getLink());
	assert(tutorialsWatchList[0].getNumberOfLikes() == tutorialsDatabase[0].getNumberOfLikes());

	userTestService.addTutorialToWatchList(tutorialsDatabase[1]);

	tutorialsWatchList = userTestService.getWatchList();

	assert(tutorialsWatchList.size() == 2);
	assert(tutorialsWatchList[1] == tutorialsDatabase[1]);
	assert(tutorialsWatchList[1].getLink() == tutorialsDatabase[1].getLink());
	assert(tutorialsWatchList[1].getNumberOfLikes() == tutorialsDatabase[1].getNumberOfLikes());


	// test likeTutorial
	userTestService.likeTutorial(tutorialsDatabase[5]);
	tutorialsDatabase = userTestService.getAllTutorialsFromDatabase();

	assert(tutorialsDatabase[5].getNumberOfLikes() == 13);

	try
	{
		userTestService.deleteTutorialFromWatchList("you won't find this", "neither this", true);
		assert(false);
	}
	catch (std::exception& e)
	{
		assert(true);
	}

	userTestService.deleteTutorialFromWatchList("Learn C++", "some indian guy", true);
	tutorialsWatchList = userTestService.getWatchList();
	tutorialsDatabase = userTestService.getAllTutorialsFromDatabase();

	assert(tutorialsWatchList.size() == 1);
	assert(tutorialsDatabase[0].getNumberOfLikes() == 1001);
	assert(testTutorialsRepo.getTutorialAtIndex(0).getNumberOfLikes() == 1001);

	userTestService.deleteTutorialFromWatchList("Make C++ easy", "Learn Together", false);
	tutorialsWatchList = userTestService.getWatchList();

	assert(tutorialsWatchList.size() == 0);
}


void Testing::testAllTutorialsWithPresenter()
{
	FakeRepository repoWithNoTutorial;
	FileWatchList* demoWatchList = new CSVWatchList{ "demo_test.txt" };

	UserService testService{ repoWithNoTutorial, demoWatchList };

	assert(testService.getTutorialsWithPresenter("").size() == 0);
	assert(testService.getTutorialsWithPresenter("John").size() == 0);
}


void Testing::testAll()
{
	std::cout << "Start all tests...\n";

	testDuration();
	std::cout << "Duration tests passed!\n";

	testTutorial();
	std::cout << "Tutorial tests passed!\n";

	testTutorialValidator();
	std::cout << "Tutorial validator tests passed!\n";

	testRepository();
	std::cout << "Repository tests passed!\n";

	testAdministratorService();
	std::cout << "Administrator service tests passed!\n";

	testUserService();
	std::cout << "User service tests passed!\n";

	std::cout << "All tests passed :)\n";
}
