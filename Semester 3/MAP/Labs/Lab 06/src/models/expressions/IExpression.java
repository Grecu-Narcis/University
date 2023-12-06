package models.expressions;

import exceptions.InterpreterException;
import models.values.IValue;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) throws InterpreterException;
}
