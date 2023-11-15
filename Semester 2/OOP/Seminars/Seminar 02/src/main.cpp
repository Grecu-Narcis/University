#include <iostream>
#include <crtdbg.h>
#include "DynamicVector.h"
#include "Source.h"
#include <assert.h>

using namespace std;

void testDynamicVector()
{
	DynamicVector<int> vect1{1};
	vect1.add(2);
	vect1.add(3);
	assert(vect1.getSize() == 2);

	DynamicVector<int> vect2{vect1};
	// DynamicVector<int> vect2 = vect1;

	DynamicVector<int> vect3{};
	vect3.add(100);
	assert(vect3.getSize() == 1);

	vect3 = vect2 = vect1;
	//vect3.operator=(vect2.operator=(vect1));

	assert(vect2.getSize() == 2);
	assert(vect3.getSize() == 2);
}

int main()
{
	/*{
		Song s{ "Pink Floyd", "Comfortably numb", 360 };
		cout << s.getTitle();
	}

	Song* s1 = new Song{ "A1", "T1", 300 };
	delete s1;*/

	testDynamicVector();

	_CrtDumpMemoryLeaks();

	return 0;
}