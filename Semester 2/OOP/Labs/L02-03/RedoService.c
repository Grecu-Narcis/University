#include "RedoService.h"

#include <stdlib.h>

RedoService* createRedoService()
{
	RedoService* createdRedoService = malloc(sizeof(RedoService));

	if (createdRedoService == NULL)
		return NULL;

	createdRedoService->redoStates = createDynamicArray(2, deleteArray);

	return createdRedoService;
}

void addRedoState(RedoService* redoService, DynamicArray* stateToAdd)
{
	DynamicArray* copyOfState = deepCopyArrayOfProducts(stateToAdd);

	addElement(redoService->redoStates, copyOfState);
}

DynamicArray* popRedoState(RedoService* redoService)
{
	if (redoService->redoStates->size == 0)
		return NULL;

	int lastItemIndex = redoService->redoStates->size - 1;

	DynamicArray* currentState = redoService->redoStates->elements[lastItemIndex];

	redoService->redoStates->size -= 1;

	return currentState;
}

void deleteRedoService(RedoService* redoService)
{
	deleteArray(redoService->redoStates);
	free(redoService);
}
