package models.expressions;

import exceptions.InterpreterException;
import models.types.Type;
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
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) {
        return symbolTable.get(id);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!typeTable.isDefined(id))
            throw new InterpreterException(String.format("Variable %s is not defined!", id));

        return typeTable.get(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
