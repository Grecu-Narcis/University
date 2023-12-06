package models.statements;

import models.ProgramState;

public class NOPStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState currentState) {
        return null;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}
