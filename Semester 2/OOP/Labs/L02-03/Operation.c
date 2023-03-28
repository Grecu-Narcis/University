#include "Operation.h"
#include "Product.h"

#include <stdlib.h>

Operation* createOperation(int(*functionForUndo)(Product* productForUndo), int(*functionForRedo)(Product* productForRedo), Product* affectedProduct)
{
	Operation* createdOperation = malloc(sizeof(Operation));

	if (createdOperation == NULL)
		return NULL;

	createdOperation->functionForUndo = functionForUndo;
	createdOperation->functionForRedo = functionForRedo;

	createdOperation->affectedProduct = deepCopyProduct(affectedProduct);

	return createdOperation;
}

void destroyOperation(Operation* operationToDestroy)
{
	if (operationToDestroy == NULL)
		return;

	deleteProduct(operationToDestroy->affectedProduct);

	free(operationToDestroy);
}

Operation* deepCopyOperation(Operation* operationToCopy)
{
	Operation* newOperation = malloc(sizeof(Operation));

	if (newOperation == NULL)
		return NULL;

	newOperation->functionForUndo = operationToCopy->functionForUndo;
	newOperation->functionForRedo = operationToCopy->functionForRedo;

	newOperation->affectedProduct = deepCopyProduct(operationToCopy->affectedProduct);

	return newOperation;
}
