package business;

import exceptions.InterpreterException;
import exceptions.StackException;
import infrastructure.IRepository;
import models.statements.IStatement;
import models.adts.MyIStack;
import models.ProgramState;
import models.values.IValue;
import models.values.ReferenceValue;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller {
    private final IRepository programsRepository;

    public Controller(IRepository programs)
    {
        this.programsRepository = programs;
    }

    /**
     * Adds a program state to the repository.
     *
     * @param programToAdd The ProgramState to be added to the repository.
     */
    public void addProgram(ProgramState programToAdd)
    {
        programsRepository.addProgram(programToAdd);
    }

    /**
     * Executes one statement from the top of the execution stack of the given ProgramState.
     *
     * @param currentState The current program state.
     * @return The updated ProgramState after executing one statement.
     * @throws InterpreterException if an error occurs during statement execution.
     */
    public ProgramState executeOneStatement(ProgramState currentState) throws InterpreterException {
        MyIStack<IStatement> exeStack = currentState.getStack();

        try {
            IStatement currentStatement = exeStack.pop();
            return currentStatement.execute(currentState);
        }
        catch (StackException e)
        {
            throw new InterpreterException("Statements stack is empty!");
        }
    }

    /**
     * Executes all statements in the program state until the execution stack is empty.
     * Logs the program state after executing each statement.
     *
     * @throws IOException if an I/O error occurs during logging.
     * @throws InterpreterException if an error occurs during statement execution.
     */
    public void executeAllStatements() throws IOException, InterpreterException
    {
        ProgramState currentState = programsRepository.getCurrentProgram();

        while (!currentState.getStack().isEmpty())
        {
            this.executeOneStatement(currentState);
            this.programsRepository.logProgramState();
            this.updateHeap();
        }
    }

    /**
     *
     * @param symbolTableAddresses all heap addresses used by variables from symbol table
     * @param heapTable current program heap table
     * @return a new map representing the new heap table
     */
    private Map<Integer, IValue> garbageCollector(List<Integer> symbolTableAddresses, Map<Integer, IValue> heapTable)
    {
        return heapTable.entrySet().stream()
                .filter(value -> symbolTableAddresses.contains(value.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    /**
     * Updates the heap table of the first program in the repository by performing garbage collection.
     * Garbage collection involves retaining only the values associated with heap addresses used by variables
     * in the symbol tables of all programs.
     */
    private void updateHeap()
    {
        ProgramState firstProgram = this.programsRepository.getCurrentProgram();

        firstProgram.getHeapTable().setContent(
                this.garbageCollector(
                        this.getAddressesFromSymbolTable(
                                firstProgram.getSymbolTable().getContent().values(),
                                firstProgram.getHeapTable().getContent()
                        ),
                        firstProgram.getHeapTable().getContent()
                ));
    }

    /**
     *
     * @param symbolTable all values from the symbol table
     * @param heapTable current program heap table
     * @return list of all used address from heap table
     */
    private List<Integer> getAddressesFromSymbolTable(Collection<IValue> symbolTable, Map<Integer, IValue> heapTable)
    {
        List<Integer> allAddresses = new ArrayList<>();

        symbolTable.stream()
                .filter(value -> value instanceof ReferenceValue)
                .forEach( value -> {
                    while (value instanceof ReferenceValue) {
                        allAddresses.add(((ReferenceValue) value).getHeapAddress());
                        value = heapTable.get(((ReferenceValue) value).getHeapAddress());
                    }
                });

        return allAddresses;
    }
}
