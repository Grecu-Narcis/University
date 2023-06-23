#include "Testing.h"
#include "Tutorial.h"
#include "DynamicArray.h"
#include "Repository.h"
#include "AdministratorService.h"
#include "UserService.h"

#include <cassert>
#include <stdexcept>


void Testing::testDuration()
{
	Duration testDuration;
	Duration testDuration1(2, 4);

	assert(testDuration.minutes == 0);
	assert(testDuration.seconds == 0);

	assert(testDuration1.minutes == 2);
	assert(testDuration1.seconds == 4);
}

void Testing::testTutorial()
{
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


void Testing::testDynamicArray()
{
	DynamicArray<int> testArray(2);

	assert(testArray.getSize() == 0);
	assert(testArray.getCapacity() == 2);

	for (int i = 0; i < 10; i++)
		testArray.pushBack(i);

	assert(testArray.getSize() == 10);
	assert(testArray[2] == 2);

	testArray.removeElementAtIndex(5);

	assert(testArray.getSize() == 9);
	assert(testArray[5] == 6);
	assert(testArray[5] == testArray.getElementAtIndex(5));

	// test exceptions

	try 
	{
		testArray.getElementAtIndex(100);
		assert(false);
	}
	catch (std::out_of_range& exception)
	{
		assert(string(exception.what()) == "Index out of range!");
	}

	try
	{
		int testValue = testArray[100];
		assert(false);
	}
	catch (std::out_of_range& exception)
	{
		assert(string(exception.what()) == "Index out of range!");
	}

	try
	{
		testArray.removeElementAtIndex(251);
		assert(false);
	}
	catch (std::out_of_range& exception)
	{
		assert(string(exception.what()) == "Index out of range!");
	}
}

void Testing::testRepository()
{
	TutorialsRepository testRepo;

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

	catch (std::exception& thrownException)
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

	catch (std::exception& thrownException)
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

	catch (std::exception& thrownException)
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
	catch (std::out_of_range& thrownException)
	{
		assert(string(thrownException.what()) == "Index out of range! - Repository");
	}

	try
	{
		testRepo.getTutorialAtIndex(7);
		assert(false);
	}
	catch (std::out_of_range& thrownException)
	{
		assert(string(thrownException.what()) == "Index out of range! - Repository");
	}
}

void Testing::testAdministratorService()
{
	TutorialsRepository testRepo;
	AdministratorService testService(testRepo);
	DynamicArray<Tutorial> allTutorials;

	Tutorial testTutorial("test title", "test presenter", "test link", 5, Duration(5, 23));

	// test add
	testService.addTutorial("test title", "test presenter", "test link", 5, 5, 23);
	allTutorials = testService.getAllTutorials();
	
	assert(allTutorials.getSize() == 1);
	assert(allTutorials[0] == testTutorial);

	// test add Exception

	try
	{
		testService.addTutorial("test title", "test presenter", "test link", 5, 5, 23);
		assert(false);
	}

	catch (std::exception& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial already in repository!");
	}


	// test update
	// Tutorial testTutorial2("test title", "test presenter", "test link", 6, Duration(5, 23));
	testService.updateTutorial("test title", "test presenter", "test link", 6, 5, 23);
	allTutorials = testService.getAllTutorials();

	assert(allTutorials.getSize() == 1);
	assert(allTutorials[0].getNumberOfLikes() == 6);

	// test update exception

	try
	{
		testService.updateTutorial("random title", "test presenter", "test link", 6, 5, 23);
		assert(false);
	}

	catch (std::exception& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial not in repository!");
	}

	
	// test delete

	testService.deleteTutorial("test title", "test presenter");
	allTutorials = testService.getAllTutorials();

	assert(allTutorials.getSize() == 0);

	try
	{
		testService.deleteTutorial("test title", "test presenter");
		assert(false);
	}

	catch (std::exception& thrownException)
	{
		assert(string(thrownException.what()) == "Tutorial not in repository!");
	}
}

void Testing::testUserService()
{
	TutorialsRepository testTutorialsRepo;
	testTutorialsRepo.addSampleData();

	UserService userTestService(testTutorialsRepo);

	// test getTutorialsWithPresenter 
	DynamicArray<Tutorial> tutorialsWithPresenter = userTestService.getTutorialsWithPresenter("nothing");

	assert(tutorialsWithPresenter.getSize() == 0);

	tutorialsWithPresenter = userTestService.getTutorialsWithPresenter("Bocicor Iuliana");
	assert(tutorialsWithPresenter.getSize() == 1);
	assert(tutorialsWithPresenter[0].getTitle() == string("Advanced C++"));
	assert(tutorialsWithPresenter[0].getPresenter() == string("Bocicor Iuliana"));
	assert(tutorialsWithPresenter[0].getLink() == string("www.cs.ubbcluj.ro"));
	assert(tutorialsWithPresenter[0].getNumberOfLikes() == 15240);
	assert(tutorialsWithPresenter[0].getDuration().minutes == 90);
	assert(tutorialsWithPresenter[0].getDuration().seconds == 15);

	tutorialsWithPresenter = userTestService.getTutorialsWithPresenter("");
	assert(tutorialsWithPresenter.getSize() == 10);
	

	// test addTutorialToWatchList and getWatchList
	DynamicArray<Tutorial> tutorialsWatchList = userTestService.getWatchList();
	DynamicArray<Tutorial> database = userTestService.getAllTutorialsFromDatabase();

	assert(tutorialsWatchList.getSize() == 0);
	
	userTestService.addTutorialToWatchList(database[0]);


	tutorialsWatchList = userTestService.getWatchList();

	assert(tutorialsWatchList.getSize() == 1);
	assert(tutorialsWatchList[0] == database[0]);
	assert(tutorialsWatchList[0].getLink() == database[0].getLink());
	assert(tutorialsWatchList[0].getNumberOfLikes() == database[0].getNumberOfLikes());

	userTestService.addTutorialToWatchList(database[1]);

	tutorialsWatchList = userTestService.getWatchList();

	assert(tutorialsWatchList.getSize() == 2);
	assert(tutorialsWatchList[1] == database[1]);
	assert(tutorialsWatchList[1].getLink() == database[1].getLink());
	assert(tutorialsWatchList[1].getNumberOfLikes() == database[1].getNumberOfLikes());


	// test likeTutorial
	userTestService.likeTutorial(database[5]);
	assert(database[5].getNumberOfLikes() == 13);

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
	database = userTestService.getAllTutorialsFromDatabase();

	assert(tutorialsWatchList.getSize() == 1);
	assert(database[0].getNumberOfLikes() == 1001);
	assert(testTutorialsRepo.getTutorialAtIndex(0).getNumberOfLikes() == 1001);

	userTestService.deleteTutorialFromWatchList("Make C++ easy", "Learn Together", false);
	tutorialsWatchList = userTestService.getWatchList();

	assert(tutorialsWatchList.getSize() == 0);
}


void Testing::testAll()
{
	std::cout << "Start all tests...\n";

	testDuration();
	std::cout << "Duration tests passed!\n";

	testTutorial();
	std::cout << "Tutorial tests passed!\n";

	testDynamicArray();
	std::cout << "Dynamic array tests passed!\n";

	testRepository();
	std::cout << "Repository tests passed!\n";

	testAdministratorService();
	std::cout << "Administrator service tests passed!\n";

	testUserService();
	std::cout << "User service tests passed!\n";

	std::cout << "All tests passed :)\n";
}
