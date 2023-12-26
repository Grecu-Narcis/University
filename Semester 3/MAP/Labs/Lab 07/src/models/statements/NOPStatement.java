package models.statements;

import exceptions.InterpreterException;
import models.ProgramState;
import models.adts.MyIDictionary;
import models.types.Type;

public class NOPStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState currentState) {
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return typeTable;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}
