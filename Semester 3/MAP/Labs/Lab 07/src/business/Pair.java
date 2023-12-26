package business;

import exceptions.InterpreterException;
import models.ProgramState;

public class Pair {
    final ProgramState program;
    final InterpreterException thrownException;

    public Pair(ProgramState program, InterpreterException thrownException)
    {
        this.program = program;
        this.thrownException = thrownException;
    }
}
