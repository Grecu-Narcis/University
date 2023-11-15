package models.statements;

import exceptions.InterpreterException;
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
    public PrgState execute(PrgState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();

        if (symbolTable.isDefined(variableId))
            throw new InterpreterException("Variable already defined!");

        symbolTable.put(variableId, variableType.defaultValue());

        return currentState;
    }

    @Override
    public String toString() {
        return variableType + " " + variableId;
    }
}
