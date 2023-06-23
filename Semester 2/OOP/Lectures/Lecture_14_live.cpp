#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Activity
{
	std::string desc, time;

public:
	Activity(const std::string& desc, const std::string& time) :
		desc{ desc }, time{ time } {}

	friend std::ostream& operator<<(std::ostream& os,
		const Activity& a) {
		os << "Activity " << a.desc << " will take place at " << a.time << "\n";
		return os;
	}
};

template <typename T>
class ToDo
{
private:
	std::vector<T> todos;

public:
	ToDo& operator+=(const T& elem)
	{
		this->todos.push_back(elem);
		return *this;
	}

	typename std::vector<T>::iterator begin()
	{
		return this->todos.begin();
	}

	typename std::vector<T>::iterator end()
	{
		return this->todos.end();
	}

	void reversePrint(std::ostream& os)
	{
		for (int i = this->todos.size() - 1; i >= 0; i--)
			os << this->todos[i];
	}
};

void ToDoList()
{
	ToDo<Activity> todo{};
	Activity tiff{ "go to TIFF movie", "20:00" };
	todo += tiff;
	Activity project{ "present project assignment", "09.20" };
	todo += project;

	// iterates through the activities and prints them as follows:
	// Activity go to TIFF movie will take place at 20.00.
	// Activity present project assignment will take place at 09.20.
	for (auto a : todo)
		std::cout << a << '\n';

	// Prints the activities as follows:
	// Activity present project assignment will take place at 09.20.
	// Activity go to TIFF movie will take place at 20.00.
	todo.reversePrint(std::cout);
}

using namespace std;

class Beverage {
private:
	std::string description;

public:
	Beverage() {}

	Beverage(const std::string& desc) : description{ desc } {}

	virtual double price() = 0;

	virtual void print() {
		cout << description << " " << price() << endl;
	}

	virtual ~Beverage() {}
};

class Coffee : public Beverage {
public:
	Coffee() : Beverage{ "Coffee" } {}
	double price() override {
		return 2.5;
	}
};

class Tea : public Beverage {
public:
	Tea() : Beverage{ "Tea" } {}
	double price() override {
		return 1.5;
	}
};


class BeverageWithMilk : public Beverage
{
private:
	Beverage* bev;
	int milkCount;

public:
	BeverageWithMilk(Beverage* b, int m) : bev{ b }, milkCount{ m } {}
	double price() override {
		return bev->price() + milkCount * 0.5;
	}

	void print() override {
		bev->print();
		cout << " with portions of milk: " << milkCount << endl;
	}
};


int main()
{
	ToDoList();

	Beverage* tea = new Tea{};
	tea->print();
	cout << "\tTotal price: " << tea->price() << endl;

	Beverage* coffee = new Coffee{};
	Beverage* coffeeWithMilk = new BeverageWithMilk{ coffee, 1 };
	coffeeWithMilk->print();
	cout << "\tTotal price: " << coffeeWithMilk->price() << endl;

	Beverage* coffeeWithDoubleMilk = new BeverageWithMilk{ coffee, 2 };
	//Beverage* coffeeWithDoubleMilk = new BeverageWithMilk{ coffeeWithMilk, 1 };
	coffeeWithDoubleMilk->print();
	cout << "\tTotal price: " << coffeeWithDoubleMilk->price();

	// TODO: memory deallocations!

	return 0;
}