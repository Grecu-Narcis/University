#pragma once

#include "Service.h"

class UI
{
private:
	Service& playersService;

public:
	UI(Service& playersService);

	void printMenu();
	void mainMenu();
	void addPlayerMenu();
};