#include "Subject.h"

void Subject::addObserver(Observer* observerToAdd)
{
	this->observers.push_back(observerToAdd);
}

void Subject::notify()
{
	for (auto& observer : observers)
		observer->update();
}
