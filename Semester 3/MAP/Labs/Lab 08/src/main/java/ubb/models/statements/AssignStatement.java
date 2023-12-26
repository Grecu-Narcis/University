package ubb.models.statements;

import ubb.exceptions.InterpreterException;
import ubb.models.types.Type;
import ubb.models.values.IValue;
import ubb.models.adts.MyIDictionary;
import ubb.models.ProgramState;
import ubb.models.expressions.IExpression;
import ubb.models.adts.MyIHeap;

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
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
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
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type expressionType = expressionToAssign.typeCheck(typeTable);

        if (!typeTable.isDefined(variableId))
            throw new InterpreterException(String.format("Variable %s is not defined!", variableId));

        Type variableType = typeTable.get(variableId);

        if (!variableType.equals(expressionType))
            throw new InterpreterException("Assignment: Left hand side and right hand side have different types!");

        return typeTable;
    }

    @Override
    public String toString() {
        return variableId + "=" + expressionToAssign;
    }
}
