#pragma once
#include "Controller.h"

class UI
{
private:
	Controller& departmentsController;

public:
	UI(Controller& departmentsController) : departmentsController{ departmentsController } {};
	
	void printMenu();
	void start();

	void addDepartmentMenu();

};

