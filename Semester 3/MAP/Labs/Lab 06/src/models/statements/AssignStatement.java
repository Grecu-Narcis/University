package models.statements;

import exceptions.InterpreterException;
import models.values.IValue;
import models.utils.MyIDictionary;
import models.PrgState;
import models.expressions.IExpression;
import models.utils.MyIHeap;

public class AssignStatement implements IStatement {
    private final String variableId;
    private final IExpression expressionToAssign;

    public AssignStatement(String variableId, IExpression expressionToAssign)
    {
        this.variableId = variableId;
        this.expressionToAssign = expressionToAssign;
    }

    /**
     * Executes an assignment statement, updating the value of a variable with the result of evaluating an expression.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the assignment statement.
     * @throws InterpreterException If the variable is not defined, or if the type of the assigned value
     *                                       does not match the type of the variable.
     */
    @Override
    public PrgState execute(PrgState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " ";

        // Check if the variable is defined in the symbol table
        if (!symbolTable.isDefined(variableId))
            throw new InterpreterException(errorThreadIdentifier + "Variable " + variableId + " is not defined!");

        IValue valueToAssign = expressionToAssign.evaluate(symbolTable, heapTable, currentState.getId());

        IValue variableValue = symbolTable.get(variableId);

        // Check if the types of the assigned value and the variable match
        if (!valueToAssign.getType().equals(variableValue.getType()))
            throw new InterpreterException(errorThreadIdentifier + "Type of variable do not match type of expression!");

        // Update the value of the variable in the symbol table
        symbolTable.put(variableId, valueToAssign);

        return null;
    }

    @Override
    public String toString() {
        return variableId + "=" + expressionToAssign;
    }
}