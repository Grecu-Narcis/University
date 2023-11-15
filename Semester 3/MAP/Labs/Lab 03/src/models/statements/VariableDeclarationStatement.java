package models.statements;

// TODO: add custom exceptions

import exceptions.StatementException;
import models.*;
import models.types.*;
import models.utils.MyIDictionary;

public class VariableDeclarationStatement implements IStatement {
    private final String variableId;
    private final Type variableType;

    public VariableDeclarationStatement(String variableId, Type variableType)
    {
        this.variableId = variableId;
        this.variableType = variableType;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();

        if (symbolTable.isDefined(variableId))
            throw new StatementException("Variable already defined!");

        if (variableType.equals(new IntType()))
            symbolTable.put(variableId, new IntValue(0));

        else
            symbolTable.put(variableId, new BoolValue(false));

        return currentState;
    }

    @Override
    public String toString() {
        return "(" + variableType + " " + variableId +  ')';
    }
}
