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

public class AllocateStatement implements IStatement {
    // USAGE: new(variable, value) translates into -> new AllocateStatement(variable, value);
    private final String variableName;
    private final IExpression expressionToEvaluate;

    public AllocateStatement(String variableName, IExpression expression)
    {
        this.variableName = variableName;
        this.expressionToEvaluate = expression;
    }


    /**
     * Executes an AllocateStatement, allocating memory in the heap for a variable of reference type
     * and updating its address with the result of evaluating an expression.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the allocate statement.
     * @throws InterpreterException If the variable is not defined, not of reference type,
     *                                       or if the expression does not match the location type.
     * @throws InterpreterException          If an error occurs during heap allocation.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " ";

        // if the variable we want to allocate is not defined stop
        if (!symbolTable.isDefined(variableName))
            throw new InterpreterException(errorThreadIdentifier + "Variable: " + variableName + " is not defined in symbol table!");

        // if the variable we want to allocate is not of reference type we stop
        if (!(symbolTable.get(variableName).getType() instanceof ReferenceType))
            throw new InterpreterException(errorThreadIdentifier + "Variable: " + variableName + " is not of reference type!");

        // get the variable from symbol table and evaluate the expression
        ReferenceValue variableToAllocate = (ReferenceValue) symbolTable.get(variableName);
        IValue expressionValue = expressionToEvaluate.evaluate(symbolTable, heapTable, currentState.getId());

        // get the ReferenceType of the variable from symbol table for further accessing the inner type
        ReferenceType variableType = (ReferenceType) variableToAllocate.getType();

        // check if the inner type is same as expression type
        if (!expressionValue.getType().equals(variableType.getInnerType()))
            throw new InterpreterException(errorThreadIdentifier + "Expression does not match location type!");

        // allocate and update the address of the reference
        int addressOfVariable = heapTable.allocate(expressionValue);
        // variableToAllocate.setHeapAddress(addressOfVariable);

        symbolTable.update(variableName, new ReferenceValue(addressOfVariable, variableType.getInnerType()));

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type variableType = typeTable.get(variableName);
        Type expressionType = expressionToEvaluate.typeCheck(typeTable);

        if (!variableType.equals(new ReferenceType(expressionType)))
            throw new InterpreterException("Allocate: left hand side and right hand side have different types!");

        return typeTable;
    }

    @Override
    public String toString() {
        return "new(" + variableName + ", " + expressionToEvaluate.toString() + ")";
    }
}
