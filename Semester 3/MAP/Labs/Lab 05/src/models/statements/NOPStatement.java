package models.statements;

import models.PrgState;

public class NOPStatement implements IStatement {
    @Override
    public PrgState execute(PrgState currentState) {
        return null;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}
