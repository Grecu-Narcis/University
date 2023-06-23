#ifndef __OPERATION_H__
#define __OPERATION_H__

#include "Product.h"

typedef struct
{
	int (*functionForUndo)(Product* productForUndo);
	int (*functionForRedo)(Product* productForRedo);

	Product* affectedProduct;
} Operation;

Operation* createOperation(int (*functionForUndo)(Product* productForUndo), int (*functionForRedo)(Product* productForRedo), Product* affectedProduct);
void destroyOperation(Operation* operationToDestroy);
Operation* deepCopyOperation(Operation* operationToCopy);

#endif