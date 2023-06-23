#include "UndoServiceEfficient.h"

#include <stdlib.h>

EfficientUndoService* createEfficientUndoService()
{
	EfficientUndoService* undoService = malloc(sizeof(EfficientUndoService));

	if (undoService == NULL)
		return NULL;

	undoService->operations = createDynamicArray(2, destroyOperation);

	return undoService;
}

void destroyEfficientUndoService(EfficientUndoService* undoService)
{
	if (undoService == NULL)
		return;

	deleteArray(undoService->operations);
	free(undoService);
}

void addUndoOperation(EfficientUndoService* undoService, Operation* operationToAdd)
{
	if (undoService == NULL)
		return;

	addElement(undoService->operations, operationToAdd);
}

Operation* getLastUndoOperation(EfficientUndoService* undoService)
{
	if (undoService->operations->size == 0)
		return NULL;

	return undoService->operations->elements[undoService->operations->size - 1];
}

void removeLastUndoOperation(EfficientUndoService* undoService)
{
	if (undoService == NULL)
		return;

	destroyOperation(getElementAtIndex(undoService->operations, getSize(undoService->operations) - 1));
	undoService->operations->size -= 1;
}
