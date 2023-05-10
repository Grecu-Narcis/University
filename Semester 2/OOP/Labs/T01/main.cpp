#include "Repository.h"
#include "Service.h"
#include "UI.h"
#include "Testing.h"

int main()
{
	runAllTests();

	Repository playersRepository;
	Service playersService(playersRepository);
	UI appUI(playersService);

	appUI.mainMenu();
}