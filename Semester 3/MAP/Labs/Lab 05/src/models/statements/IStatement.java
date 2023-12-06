package models.statements;

import exceptions.InterpreterException;
import models.ProgramState;

public interface IStatement {
    ProgramState execute(ProgramState currentState) throws InterpreterException;
}
