package models.expressions;

import exceptions.ExpressionEvaluationException;
import models.types.IValue;
import models.types.IntType;
import models.types.IntValue;
import models.utils.MyIDictionary;

public class ArithmeticExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final char operation;

    public ArithmeticExpression(char operation, IExpression firstExpression, IExpression secondExpression)
    {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable) throws ExpressionEvaluationException {
        IValue firstValue, secondValue;
        firstValue = firstExpression.evaluate(symbolTable);
        secondValue = secondExpression.evaluate(symbolTable);

        if (!firstValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("First operand is not integer!");

        if (!secondValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("Second operand is not integer!");

        IntValue firstOperand = (IntValue) firstValue;
        IntValue secondOperand = (IntValue) secondValue;

        int firstNumber = firstOperand.getValue();
        int secondNumber = secondOperand.getValue();

        switch (operation)
        {
            case '+':
                return new IntValue(firstNumber + secondNumber);

            case '-':
                return new IntValue(firstNumber - secondNumber);

            case '*':
                return new IntValue(firstNumber * secondNumber);

            case '/':
                if (secondNumber == 0)
                    throw new ExpressionEvaluationException("Division by 0!");

                return new IntValue(firstNumber / secondNumber);
        }

        return null;
    }

    @Override
    public String toString() {

        return switch (operation) {
            case '+' -> "(" + firstExpression.toString() + "+" + secondExpression.toString() + ")";
            case '-' -> "(" + firstExpression.toString() + "-" + secondExpression.toString() + ")";
            case '*' -> "(" + firstExpression.toString() + "*" + secondExpression.toString() + ")";
            case '/' -> "(" + firstExpression.toString() + "/" + secondExpression.toString() + ")";
            default -> "";
        };
    }
}
