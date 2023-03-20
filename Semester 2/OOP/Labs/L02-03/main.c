#include "Product.h"
#include "DynamicArray.h"
#include "Repository.h"
#include "UI.h"

#include <stdlib.h>
#include <crtdbg.h>

void addSampleProducts(Repository* productsRepository)
{
	Product* productToAdd;

	productToAdd = createProduct("apples", "fruit", 3, createDate(5, 9, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("pears", "fruit", 5, createDate(12, 4, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("eggs", "dairy", 30, createDate(30, 10, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("beef", "meat", 1, createDate(12, 12, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("chocolate", "sweets", 5, createDate(5, 3, 2025));
	addProductToRepository(productsRepository, productToAdd);
}

int main()
{
	Repository* productsRepository = createRepository();
	UndoService* undoService = createUndoService();
	RedoService* redoService = createRedoService();
	Service* productsService = createService(productsRepository, undoService, redoService);
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
