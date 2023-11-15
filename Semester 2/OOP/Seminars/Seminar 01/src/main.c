#include "Planet.h"
#include "DynamicArray.h"
#include <crtdbg.h>

int main()
{
	Planet* p = createPlanet("HD 189733 b", "a blue-ish planet", 10);
	destroyPlanet(p);

	DynamicArray* arr = createArray(2, destroyPlanet);

	
	//testDynamicArray();

	_CrtDumpMemoryLeaks();

	return 0;
}

// 0x91b60
// 0x91bb0