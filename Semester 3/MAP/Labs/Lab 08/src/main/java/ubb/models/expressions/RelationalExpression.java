package ubb.models.expressions;

import ubb.exceptions.InterpreterException;
import ubb.models.types.BoolType;
import ubb.models.types.Type;
import ubb.models.values.BoolValue;
import ubb.models.values.IValue;
import ubb.models.types.IntType;
import ubb.models.values.IntValue;
import ubb.models.adts.MyIDictionary;
import ubb.models.adts.MyIHeap;

public class RelationalExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final String operation;

    public RelationalExpression(IExpression firstExpression, IExpression secondExpression, String operation)
    {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    /**
     * Evaluates a relational expression involving two integer operands and a comparison operator.
     *
     * @param symbolTable The symbol table containing variable bindings.
     * @param heapTable   The heap table containing memory allocations.
     * @return A {@code BoolValue} representing the result of the relational comparison.
     * @throws InterpreterException If the operands do not evaluate to integers or if an invalid comparison operator is used.
     */
    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) throws InterpreterException {
        IValue firstValue = this.firstExpression.evaluate(symbolTable, heapTable, threadID);
        IValue secondValue = this.secondExpression.evaluate(symbolTable, heapTable, threadID);

        String errorThreadIdentifier = "Thread: " + threadID + " - ";

        // Check if the types of the operands are integers
        if (!firstValue.getType().equals(new IntType()))
            throw new InterpreterException(errorThreadIdentifier +
                    "First operand does not evaluate to an IntType!");

        if (!secondValue.getType().equals(new IntType()))
            throw new InterpreterException(errorThreadIdentifier +
                    "Second operand does not evaluate to an IntType!");

        // Extract the integer values of the operands
        int firstInteger = ((IntValue) firstValue).getValue();
        int secondInteger = ((IntValue) secondValue).getValue();

        // Perform the relational comparison based on the specified operator
        return switch (operation) {
            case "<" -> new BoolValue(firstInteger < secondInteger);
            case "<=" -> new BoolValue(firstInteger <= secondInteger);
            case "==" -> new BoolValue(firstInteger == secondInteger);
            case "!=" -> new BoolValue(firstInteger != secondInteger);
            case ">" -> new BoolValue(firstInteger > secondInteger);
            case ">=" -> new BoolValue(firstInteger >= secondInteger);
            default -> throw new InterpreterException(errorThreadIdentifier +
                    "Invalid comparison operand!");
        };
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type firstExpressionType = firstExpression.typeCheck(typeTable);
        Type secondExpressionType = secondExpression.typeCheck(typeTable);

        if (!firstExpressionType.equals(new IntType()))
            throw new InterpreterException("First operand is not integer!");

        if (!secondExpressionType.equals(new IntType()))
            throw new InterpreterException("Second operand is not integer!");

        return new BoolType();
    }

    @Override
    public String toString() {
        return this.firstExpression + this.operation + this.secondExpression;
    }
}
