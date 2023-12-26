package ubb.models.adts;

import ubb.exceptions.InterpreterException;
import ubb.models.ProgramState;

public class Pair {
    public final ProgramState program;
    public final InterpreterException thrownException;

    public Pair(ProgramState program, InterpreterException thrownException) {
        this.program = program;
        this.thrownException = thrownException;
    }
}
