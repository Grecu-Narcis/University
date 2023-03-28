#include "RedoServiceEfficient.h"

#include <stdlib.h>

EfficientRedoService* createEfficientRedoService()
{
	EfficientRedoService* redoService = malloc(sizeof(EfficientRedoService));

	if (redoService == NULL)
		return NULL;

	redoService->operations = createDynamicArray(2, destroyOperation);

	return redoService;
}

void destroyEfficientRedoService(EfficientRedoService* redoService)
{
	if (redoService == NULL)
		return;

	deleteArray(redoService->operations);
	free(redoService);
}

void addRedoOperation(EfficientRedoService* redoService, Operation* operationToAdd)
{
	if (redoService == NULL)
		return;

	addElement(redoService->operations, operationToAdd);
}

Operation* getLastRedoOperation(EfficientRedoService* redoService)
{
	if (redoService->operations->size == 0)
		return NULL;

	return redoService->operations->elements[redoService->operations->size - 1];
}

void removeLastRedoOperation(EfficientRedoService* redoService)
{
	if (redoService == NULL)
		return;

	destroyOperation(getElementAtIndex(redoService->operations, getSize(redoService->operations) - 1));
	redoService->operations->size -= 1;
}
