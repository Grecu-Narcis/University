#pragma once

#include "DynamicArray.h"

typedef struct
{
	DynamicArray* redoStates;
}RedoService;

RedoService* createRedoService();
void addRedoState(RedoService* redoService, DynamicArray* stateToAdd);
DynamicArray* popRedoState(RedoService* redoService);
void deleteRedoService(RedoService* redoService);
