#pragma once

#include "DynamicArray.h"

typedef struct
{
	DynamicArray* undoStates;
}UndoService;

UndoService* createUndoService();
void addUndoState(UndoService* undoService, DynamicArray* stateToAdd);
DynamicArray* popUndoState(UndoService* undoService);
void deleteUndoService(UndoService* undoService);
