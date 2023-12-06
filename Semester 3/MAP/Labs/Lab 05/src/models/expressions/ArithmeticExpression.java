package models.expressions;

import exceptions.InterpreterException;
import models.values.IValue;
import models.types.IntType;
import models.values.IntValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

public class ArithmeticExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final char operation;

    public ArithmeticExpression(char operation, IExpression firstExpression, IExpression secondExpression)
    {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    /**
     * Evaluates an arithmetic expression consisting of two operands and an operator.
     * Supports addition, subtraction, multiplication, and division of integer operands.
     *
     * @param symbolTable The symbol table containing variable bindings.
     * @param heapTable   The heap table containing memory allocations.
     * @return an IntValue representing the result of the arithmetic operation.
     * @throws InterpreterException If the operands are not integers, or if division by zero is attempted.
     */
    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws InterpreterException {
        IValue firstValue, secondValue;
        firstValue = firstExpression.evaluate(symbolTable, heapTable);
        secondValue = secondExpression.evaluate(symbolTable, heapTable);

        // check if both operand are integers
        if (!firstValue.getType().equals(new IntType()))
            throw new InterpreterException("First operand is not integer!");

        if (!secondValue.getType().equals(new IntType()))
            throw new InterpreterException("Second operand is not integer!");

        IntValue firstOperand = (IntValue) firstValue;
        IntValue secondOperand = (IntValue) secondValue;

        // get the value of each operand
        int firstNumber = firstOperand.getValue();
        int secondNumber = secondOperand.getValue();

        // compute the specified operation
        return switch (operation) {
            case '+' -> new IntValue(firstNumber + secondNumber);
            case '-' -> new IntValue(firstNumber - secondNumber);
            case '*' -> new IntValue(firstNumber * secondNumber);
            case '/' -> {
                if (secondNumber == 0)
                    throw new InterpreterException("Division by 0!");
                yield new IntValue(firstNumber / secondNumber);
            }
            default -> null;
        };

    }

    @Override
    public String toString() {

        return firstExpression.toString() + operation + secondExpression.toString();
    }
}
