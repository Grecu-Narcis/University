#pragma once
#include "Observer.h"

#include <vector>

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void registerObserver(Observer* observerToAdd);
	void unregisterObserver(Observer* observerToRemove);

	void notify();
};

