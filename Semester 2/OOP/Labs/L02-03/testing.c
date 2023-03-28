#include "testing.h"
#include "DynamicArray.h"
#include "Repository.h"
#include "ProductsService.h"

#include <assert.h>
#include <string.h>

void testDynamicArray()
{
	DynamicArray* arrayForTest = createDynamicArray(2, deleteProduct);

	assert(arrayForTest->capacity == 2);
	assert(arrayForTest->size == 0);

	Product* product = createProduct("apples", "fruit", 2, createDate(12, 12, 2023));
	addElement(arrayForTest, product);

	assert(getElementAtIndex(arrayForTest, 0) == product);
	assert(arrayForTest->capacity == 2);
	assert(arrayForTest->size == 1);

	// deleteProduct(product);
	deleteArray(arrayForTest);
}

void testRepository()
{
	Repository* repoForTest = createRepository();

	addSampleProducts(repoForTest); // adds 5 products

	assert(repoForTest->products->size == 5);

	DynamicArray* allProducts = getAllProductsFromRepository(repoForTest);

	Product* firstProduct = getElementAtIndex(allProducts, 0);
	assert(strcmp(firstProduct->name, "apples") == 0);
	assert(findProductPositionInRepo(repoForTest, "beef", "meat") == 3);

	Product* productToAdd = createProduct("pork", "meat", 2, createDate(12, 12, 2023));

	addProductToRepository(repoForTest, productToAdd);

	assert(getSize(repoForTest) == 6);

	assert(removeProductFromRepository(repoForTest, "asdas", "asffjef") == -1);
	assert(removeProductFromRepository(repoForTest, "apples", "fruit") == 1);

	deleteRepository(repoForTest);
}


//void testService()
//{
//	Repository* repo = createRepository();
//	UndoService* undoService = createUndoService();
//	RedoService* redoService = createRedoService();
//	Service* service = createService(repo, undoService, redoService);
//
//	addSampleProducts(repo);
//
//	assert(serviceAddProduct(service, "apples", "fruit", 5, createDate(12, 12, 2023)) == 1);
//
//	Product* demoProduct = getElementAtIndex(service->productsRepository->products, 0);
//
//	assert(demoProduct->quantity == 8);
//
//	undoLastOperation(service);
//
//
//	DynamicArray* arrayForTest;
//	arrayForTest = getAllProductsContainingString(service, "", checkIfProductContainStringInName);
//
//	assert(arrayForTest->size == 5);
//
//	/*free(arrayForTest->elements);
//	free(arrayForTest);*/
//
//	arrayForTest = getAllProductsFromCategoryWithExpirationClose(service, "fruit", 1000, 1);
//
//	assert(arrayForTest->size == 2);
//
//	demoProduct = getElementAtIndex(arrayForTest, 0);
//
//	assert(strcmp(demoProduct->name, "pears") == 0);
//	
//	serviceAddProduct(service, "pork", "meat", 2, createDate(12, 12, 2023));
//	arrayForTest = getAllProductsContainingString(service, "", checkIfProductContainStringInName);
//
//	assert(arrayForTest->size == 6);
//
//	undoLastOperation(service);
//
//	arrayForTest = getAllProductsContainingString(service, "", checkIfProductContainStringInName);
//	assert(arrayForTest->size == 5);
//
//	redoLastOperation(service);
//
//	arrayForTest = getAllProductsContainingString(service, "", checkIfProductContainStringInName);
//	assert(arrayForTest->size == 6);
//}

void runAllTests()
{
	printf("Start testing!\n");

	testDynamicArray();
	testRepository();
	//testService();

	printf("All tests passed!\n\n\n");
}
