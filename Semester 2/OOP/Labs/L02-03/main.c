#include "Product.h"
#include "DynamicArray.h"
#include "Repository.h"
#include "UI.h"
#include "testing.h"

#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	// runAllTests();

	Repository* productsRepository = createRepository();
	UndoService* undoService = createUndoService();
	RedoService* redoService = createRedoService();
	EfficientUndoService* efficientUndoService = createEfficientUndoService();
	EfficientRedoService* efficientRedoService = createEfficientRedoService();
	Service* productsService = createService(productsRepository, undoService, redoService, efficientUndoService, efficientRedoService);
	UI* ui = createUI(productsService);

	addSampleProducts(productsRepository);

	mainMenu(ui);
	
	deleteRepository(productsRepository);
	deleteService(productsService);
	deleteUI(ui);

	_CrtDumpMemoryLeaks();

	system("pause");

	return 0;
}
