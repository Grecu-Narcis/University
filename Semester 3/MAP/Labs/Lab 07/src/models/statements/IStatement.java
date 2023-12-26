package models.statements;

import exceptions.InterpreterException;
import models.ProgramState;
import models.adts.MyIDictionary;
import models.types.Type;

public interface IStatement {
    ProgramState execute(ProgramState currentState) throws InterpreterException;
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
