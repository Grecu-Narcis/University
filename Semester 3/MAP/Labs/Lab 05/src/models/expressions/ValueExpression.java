package models.expressions;

import models.values.IValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value)
    {
        this.value = value;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) {
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
