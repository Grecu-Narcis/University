#include <iostream>

#include "lista.h"

using namespace std;

//8. a.Determine the lowest common multiple of the elements from a list.
//   b.Substitute in a list, all occurrence of a value e with a value e1.

int main()
{
	Lista l = creare();

	tipar(l);

	cout << "lcm is " << lcm(l) << endl;
	substitute(l);

	cout << "List after substitution is: \n";
	tipar(l);

	return 0;
}