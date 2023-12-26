package models.expressions;

import exceptions.InterpreterException;
import models.types.Type;
import models.values.IValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) throws InterpreterException;
    Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
