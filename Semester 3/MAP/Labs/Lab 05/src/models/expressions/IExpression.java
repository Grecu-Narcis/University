package models.expressions;

import exceptions.InterpreterException;
import models.values.IValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws InterpreterException;
}
