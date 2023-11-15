package infrastructure;

import models.PrgState;

public interface IRepository {
    void addProgram(PrgState programToAdd);
    PrgState getCurrentProgram();
}
