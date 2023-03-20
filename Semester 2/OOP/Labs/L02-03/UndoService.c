#include "UndoService.h"

#include <stdlib.h>

UndoService* createUndoService()
{
	UndoService* createdUndoService = malloc(sizeof(UndoService));

	if (createdUndoService == NULL)
		return NULL;

	createdUndoService->undoStates = createDynamicArray(2, deleteArray);

	return createdUndoService;
}


void addUndoState(UndoService* undoService, DynamicArray* stateToAdd)
{
	DynamicArray* copyOfState = deepCopyArrayOfProducts(stateToAdd);
	
	addElement(undoService->undoStates, copyOfState);
}

DynamicArray* popUndoState(UndoService* undoService)
{
	if (undoService->undoStates->size == 0)
		return NULL;

	int lastItemIndex = undoService->undoStates->size - 1;

	DynamicArray* currentState = undoService->undoStates->elements[lastItemIndex];

	undoService->undoStates->size -= 1;

	return currentState;
}

void deleteUndoService(UndoService* undoService)
{
	deleteArray(undoService->undoStates);
	free(undoService);
}
