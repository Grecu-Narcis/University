package infrastructure;

import models.PrgState;

import java.util.ArrayList;

public class ProgramsRepository implements IRepository {
    private final ArrayList<PrgState> programs;

    public ProgramsRepository()
    {
        programs = new ArrayList<PrgState>();
    }

    @Override
    public void addProgram(PrgState programToAdd) {
        if (!programs.isEmpty())
            programs.set(0, programToAdd);
        else
            programs.add(programToAdd);
    }

    @Override
    public PrgState getCurrentProgram() {
        return programs.get(0);
    }
}
