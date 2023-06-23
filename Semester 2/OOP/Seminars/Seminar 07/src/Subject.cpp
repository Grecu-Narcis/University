#include "Subject.h"

#include <algorithm>

void Subject::registerObserver(Observer* observerToAdd)
{
	this->observers.push_back(observerToAdd);
}

void Subject::unregisterObserver(Observer* observerToRemove)
{
	auto it = find(observers.begin(), observers.end(), observerToRemove);

	if (it == observers.end())
		return;

	observers.erase(it);
}

void Subject::notify()
{
	for (const auto& observer : observers)
		observer->update();
}
