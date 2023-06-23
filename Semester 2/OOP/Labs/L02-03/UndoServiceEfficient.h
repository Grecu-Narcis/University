#pragma once
#include "DynamicArray.h"
#include "Operation.h"

typedef struct
{
	DynamicArray* operations;
}EfficientUndoService;

EfficientUndoService* createEfficientUndoService();
void destroyEfficientUndoService(EfficientUndoService* undoService);
void addUndoOperation(EfficientUndoService* undoService, Operation* operationToAdd);
Operation* getLastUndoOperation(EfficientUndoService* undoService);
void removeLastUndoOperation(EfficientUndoService* undoService);
