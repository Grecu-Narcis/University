package models.expressions;

import exceptions.InterpreterException;
import models.values.BoolValue;
import models.values.IValue;
import models.types.IntType;
import models.values.IntValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

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
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws InterpreterException {
        IValue firstValue = this.firstExpression.evaluate(symbolTable, heapTable);
        IValue secondValue = this.secondExpression.evaluate(symbolTable, heapTable);

        // Check if the types of the operands are integers
        if (!firstValue.getType().equals(new IntType()))
            throw new InterpreterException("First operand does not evaluate to an IntType!");

        if (!secondValue.getType().equals(new IntType()))
            throw new InterpreterException("Second operand does not evaluate to an IntType!");

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
            default -> throw new InterpreterException("Invalid comparison operand!");
        };
    }

    @Override
    public String toString() {
        return this.firstExpression + this.operation + this.secondExpression;
    }
}
