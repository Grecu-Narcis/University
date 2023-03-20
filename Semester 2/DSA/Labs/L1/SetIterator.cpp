#include "SetIterator.h"
#include "Set.h"
#include <exception>

using namespace std;

SetIterator::SetIterator(const Set& m) : set(m)
{
	this->iteratorSet = m;
	this->position = 0;
}


void SetIterator::first() {
	this->position = 0;
}


void SetIterator::next() {
	if (!valid())
		throw exception();

	if (this->position >= this->iteratorSet.size())
		throw exception();

	this->position += 1;
}


TElem SetIterator::getCurrent() {
	if (valid())
		return this->iteratorSet.elements[this->position];

	throw exception();
}

bool SetIterator::valid() const {
	if (this->position < this->iteratorSet.size())
		return true;

	return false;
}



