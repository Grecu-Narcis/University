#pragma once

#include "Observer.h"

#include <vector>

using std::vector;

class Subject
{
private:
	vector<Observer*> observers;

public:
	void addObserver(Observer* observerToAdd);
	void notify();
};

