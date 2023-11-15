package models.expressions;

import exceptions.ExpressionEvaluationException;
import models.types.BoolValue;
import models.types.IValue;
import models.types.IntType;
import models.types.IntValue;
import models.utils.MyIDictionary;

public class RelationalExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final String operation;

    public RelationalExpression(IExpression firstExpression, IExpression secondExpression, String operation)
    {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable) throws ExpressionEvaluationException {
        IValue firstValue = this.firstExpression.evaluate(symbolTable);
        IValue secondValue = this.secondExpression.evaluate(symbolTable);

        if (!firstValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("First operand does not evaluate to an IntType!");

        if (!secondValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("Second operand does not evaluate to an IntType!");

        int firstInteger = ((IntValue) firstValue).getValue();
        int secondInteger = ((IntValue) secondValue).getValue();

        return switch (operation) {
            case "<" -> new BoolValue(firstInteger < secondInteger);
            case "<=" -> new BoolValue(firstInteger <= secondInteger);
            case "==" -> new BoolValue(firstInteger == secondInteger);
            case "!=" -> new BoolValue(firstInteger != secondInteger);
            case ">" -> new BoolValue(firstInteger > secondInteger);
            case ">=" -> new BoolValue(firstInteger >= secondInteger);
            default -> throw new ExpressionEvaluationException("Invalid comparison operand!");
        };
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
