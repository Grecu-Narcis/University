package ubb.models.expressions;

import ubb.exceptions.InterpreterException;
import ubb.models.types.Type;
import ubb.models.values.IValue;
import ubb.models.adts.MyIDictionary;
import ubb.models.adts.MyIHeap;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) throws InterpreterException;
    Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
