#pragma once
#include <string>

using std::string;

class Item
{
private:
	string category, name;
	int quantity;

public:
	Item(string category, string name, int quantity);

	string getCategory();
	string getName();
	int getQuantity();

	string toString();
};

