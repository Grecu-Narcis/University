package models.expressions;

import models.values.IValue;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;

public class VariableExpression implements IExpression {
    private final String id;

    public VariableExpression(String id)
    {
        this.id = id;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) {
        return symbolTable.get(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
