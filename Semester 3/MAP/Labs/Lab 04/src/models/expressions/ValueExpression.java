package models.expressions;

import models.types.IValue;
import models.utils.MyIDictionary;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value)
    {
        this.value = value;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable) {
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
