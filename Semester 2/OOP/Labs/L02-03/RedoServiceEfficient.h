#pragma once
#include "DynamicArray.h"
#include "Operation.h"

typedef struct
{
	DynamicArray* operations;
}EfficientRedoService;

EfficientRedoService* createEfficientRedoService();
void destroyEfficientRedoService(EfficientRedoService* redoService);
void addRedoOperation(EfficientRedoService* redoService, Operation* operationToAdd);
Operation* getLastRedoOperation(EfficientRedoService* redoService);
void removeLastRedoOperation(EfficientRedoService* redoService);
