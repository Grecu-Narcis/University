#pragma once
#include "Variable.h"

class DSM
{
public:
	Variable a, b;
	
	Variable& getVariableReference(char variableName);

	int getVariable(char variableName);
	void setVariable(char variableName, int newValue);

	void updateVariable(char variableName, int newValue, int numberOfProcesses);

	void subscribe(char variableName, int who, int numberOfProcesses);

	void addSubscriber(char variableName, int processId);
	void compareAndExchange(char variableName, int oldValue, int newValue, int numberOfProcesses);

	void shutDown(int processId);
};

