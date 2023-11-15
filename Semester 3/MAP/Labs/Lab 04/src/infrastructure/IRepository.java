package infrastructure;

import models.PrgState;

import java.io.IOException;

public interface IRepository {
    void addProgram(PrgState programToAdd);
    PrgState getCurrentProgram();
    void logProgramState() throws IOException;
}
