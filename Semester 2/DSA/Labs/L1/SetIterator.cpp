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
// BC: Theta(1), AC: Theta(1), WC: Theta(1)


void SetIterator::next() {
	if (!valid())
		throw exception();

	if (this->position >= this->iteratorSet.size())
		throw exception();

	this->position += 1;
}
// BC: Theta(1), AC: Theta(1), WC: Theta(1)


TElem SetIterator::getCurrent() {
	if (valid())
		return this->iteratorSet.elements[this->position];

	throw exception();
}
// BC: Theta(1), AC: Theta(1), WC: Theta(1)


bool SetIterator::valid() const {
	if (this->position < this->iteratorSet.size())
		return true;

	return false;
}
// BC: Theta(1), AC: Theta(1), WC: Theta(1)

