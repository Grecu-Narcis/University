#include "Item.h"

Item::Item(string category, string name, int quantity) : category{ category }, name{ name }, quantity{ quantity }
{
}

string Item::getCategory()
{
	return this->category;
}

string Item::getName()
{
	return this->name;
}

int Item::getQuantity()
{
	return this->quantity;
}

string Item::toString()
{
	return category + " | " + name + " | " + std::to_string(quantity);
}
