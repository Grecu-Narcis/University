package models.expressions;

import models.values.IValue;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value)
    {
        this.value = value;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) {
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
