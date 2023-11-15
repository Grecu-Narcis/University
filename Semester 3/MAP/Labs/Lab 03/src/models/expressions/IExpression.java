package models.expressions;

// TODO: add my exception

import exceptions.ExpressionEvaluationException;
import models.types.IValue;
import models.utils.MyIDictionary;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable) throws ExpressionEvaluationException;
}
