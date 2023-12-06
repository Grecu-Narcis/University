package infrastructure;

import models.ProgramState;

import java.io.IOException;

public interface IRepository {
    void addProgram(ProgramState programToAdd);
    ProgramState getCurrentProgram();
    void logProgramState() throws IOException;
}
