package ubb.models.statements;

import ubb.exceptions.InterpreterException;
import ubb.models.ProgramState;
import ubb.models.expressions.IExpression;
import ubb.models.types.Type;
import ubb.models.values.IValue;
import ubb.models.types.ReferenceType;
import ubb.models.values.ReferenceValue;
import ubb.models.adts.MyIDictionary;
import ubb.models.adts.MyIHeap;

public class WriteHeapStatement implements IStatement {
    private final String variableName;
    private final IExpression expressionToEvaluate;

    public WriteHeapStatement(String variableName, IExpression newValue)
    {
        this.variableName = variableName;
        this.expressionToEvaluate = newValue;
    }

    /**
     * Executes a WriteHeapStatement, updating the value stored at the address pointed to by a reference variable
     * with the result of evaluating an expression.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the write heap statement.
     * @throws InterpreterException If the variable is not defined, not of reference type, or if the
     *                                       referenced address is not defined in the heap.
     * @throws InterpreterException          If the type of the new value does not match the type of the location
     *                                       pointed by the reference variable.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " - ";

        // check if variable is defined in symbolTable
        if (!symbolTable.isDefined(variableName))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("Variable %s is not defined!", variableName));

        // check if the variable type is ReferenceType
        if (!(symbolTable.get(variableName).getType() instanceof ReferenceType))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("Variable %s is not of type reference!", variableName));

        ReferenceValue variableToModify = (ReferenceValue) symbolTable.get(variableName);

        // check if the address pointed by variable is defined in heap
        if (!heapTable.isDefined(variableToModify.getHeapAddress()))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("The address referenced by %s is not defined in heap!", variableName));

        IValue newValue = expressionToEvaluate.evaluate(symbolTable, heapTable, currentState.getId());
        ReferenceType variableType = (ReferenceType) variableToModify.getType();

        // check if type of location pointed by variable is same as type of expression
        if (!newValue.getType().equals(variableType.getInnerType()))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("New value does not have the same type as the one referenced by %s", variableName));

        heapTable.updateAddress(variableToModify.getHeapAddress(), newValue);

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!typeTable.get(variableName).equals(new ReferenceType(expressionToEvaluate.typeCheck(typeTable))))
            throw new InterpreterException("Write Heap: left hand side and right hand side have different types!");

        return typeTable;
    }

    @Override
    public String toString() {
        return "WriteHeap(" + variableName + ", " + expressionToEvaluate + ")";
    }
}
