package models.expressions;

import models.values.IValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

public class VariableExpression implements IExpression {
    private final String id;

    public VariableExpression(String id)
    {
        this.id = id;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) {
        return symbolTable.get(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
