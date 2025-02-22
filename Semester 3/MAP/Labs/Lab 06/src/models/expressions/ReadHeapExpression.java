package models.expressions;

import exceptions.InterpreterException;
import models.values.IValue;
import models.values.ReferenceValue;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;

public class ReadHeapExpression implements IExpression {
    private final IExpression expressionToEvaluate;

    public ReadHeapExpression(IExpression expressionToEvaluate)
    {
        this.expressionToEvaluate = expressionToEvaluate;
    }

    /**
     * Evaluates a ReadHeapExpression, which reads the value from the heap at the address specified by the result
     * of evaluating the inner expressionToEvaluate.
     *
     * @param symbolTable The symbol table containing variable bindings.
     * @param heapTable   The heap table containing memory allocations.
     * @return The {@code IValue} stored at the address obtained by evaluating the inner expressionToEvaluate.
     * @throws InterpreterException If the inner expression does not evaluate to a ReferenceValue,
     *                                       or if the referenced address is not allocated in the heap table.
     */
    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) throws InterpreterException {
        IValue innerExpressionValue = expressionToEvaluate.evaluate(symbolTable, heapTable, threadID);

        String errorThreadIdentifier = "Thread: " + threadID + " - ";

        // Check if the inner expression evaluates to a ReferenceValue
        if (! (innerExpressionValue instanceof ReferenceValue expressionValue))
            throw new InterpreterException(errorThreadIdentifier +
                    "Expression is not of type reference!");

        int addressToRead = expressionValue.getHeapAddress();
        IValue valueFound = heapTable.getValueAtAddress(addressToRead);

        // Check if the address is allocated in the heap table
        if (valueFound == null)
            throw new InterpreterException(errorThreadIdentifier +
                    "The address is not allocated in heap table!");

        return valueFound;
    }

    @Override
    public String toString() {
        return "ReadHeap(" + expressionToEvaluate + ")";
    }
}
