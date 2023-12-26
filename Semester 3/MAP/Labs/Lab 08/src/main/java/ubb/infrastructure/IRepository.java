package ubb.infrastructure;

import ubb.models.ProgramState;

import java.util.List;

public interface IRepository {
    void addProgram(ProgramState programToAdd);
    List<ProgramState> getAllPrograms();
    void setProgramsList(List<ProgramState> newPrograms);
    void logProgramState(ProgramState currentProgram);
}
