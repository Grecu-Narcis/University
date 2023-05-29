#ifndef __TESTING_H__
#define __TESTING_H__

#include <iostream>

class Testing
{
	static void testTutorialToString();
	static void testTutorialIsNull();

public:
	static void testDuration();
	static void testTutorial();
	static void testTutorialValidator();
	static void testRepository();
	static void testAdministratorService();
	static void testUserService();

	static void testAllTutorialsWithPresenter();

	static void testAll();
};

#endif