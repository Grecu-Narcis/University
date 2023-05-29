#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedMultiMap.h"
#include "SMMIterator.h"

bool rel1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}
int main()
{
	SortedMultiMap smm(rel1);

	smm.add(2, 100);
	smm.add(102, 102);
	smm.add(0, 0);

	SMMIterator it = smm.iterator();

	it.first();

	while (it.valid())
	{
		cout << it.getCurrent().first << " " << it.getCurrent().second << "\n";
		it.next();
	}

	smm.remove(102, 102);

	SMMIterator it1 = smm.iterator();

	it1.first();

	while (it1.valid())
	{
		cout << it1.getCurrent().first << " " << it1.getCurrent().second << "\n";
		it1.next();
	}

    /*testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;*/
	system("pause");
}
