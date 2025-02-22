#include "DSM.h"
#include "mpi_comm.h"

Variable& DSM::getVariableReference(char variableName)
{
    if (variableName == 'a')
        return this->a;

    return this->b;
}

int DSM::getVariable(char variableName)
{
    if (variableName == 'a')
        return this->a.value;

    return this->b.value;
}

void DSM::setVariable(char variableName, int newValue)
{
    if (variableName == 'a')
        this->a.value = newValue;

    else
        this->b.value = newValue;
}

void DSM::updateVariable(char variableName, int newValue, int numberOfProcesses)
{
    Variable& var = getVariableReference(variableName);
    for (auto i : var.subscribers) {
        std::cout << "send to " << i << "\n" << endl;
        sendUpdate(variableName, newValue, i);
    }

    std::cout << "done sending update\n" << flush;
}

void DSM::subscribe(char variableName, int who, int numberOfProcesses)
{
    for (int i = 0; i < numberOfProcesses; i++) {
        if (i == who)
            this->addSubscriber(variableName, who);
        else
        sendSubscribe(variableName, who, i);
    }
}

void DSM::addSubscriber(char variableName, int processId)
{
    if (variableName == 'a')
        this->a.subscribers.push_back(processId);

    else
        this->b.subscribers.push_back(processId);
}

void DSM::compareAndExchange(char variableName, int oldValue, int newValue, int numberOfProcesses)
{
    int variableValue = variableName == 'a' ? this->a.value : this->b.value;

    if (variableValue == oldValue)
        updateVariable(variableName, newValue, numberOfProcesses);
}

void DSM::shutDown(int processId)
{
    int message[] = {-1, -1, -1};

    MPI_Bsend(message, 3, MPI_INT, processId, 0, MPI_COMM_WORLD);

    cout << "sent shutdown to " << processId << endl << flush;
}
