package ubb.business;

import ubb.exceptions.InterpreterException;
import ubb.infrastructure.IRepository;
import ubb.models.values.IValue;
import ubb.models.values.ReferenceValue;
import ubb.models.ProgramState;
import ubb.models.adts.Pair;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;


public class InterpreterController {
    private final IRepository programsRepository;
    private ProgramState copyProgram;
    private ExecutorService threadsExecutor;

    public InterpreterController(IRepository programs)
    {
        this.programsRepository = programs;
        this.copyProgram = null;
    }

    /**
     * Adds a new program state to the repository.
     *
     * @param programToAdd The program state to be added.
     */

    public void addProgram(ProgramState programToAdd)
    {
        programsRepository.addProgram(programToAdd);
    }

    /**
     * Executes all steps for all programs until none are left or all programs are completed.
     *
     * @throws InterpreterException if an error occurs during program execution.
     */

    public List<ProgramState> getAllPrograms()
    {
        return this.programsRepository.getAllPrograms();
    }

    public void allSteps() throws InterpreterException
    {

        while (!programsRepository.getAllPrograms().isEmpty())
        {
            this.oneStepAll();
        }
    }

    public ProgramState getCopyProgram()
    {
        return this.copyProgram;
    }

    public void oneStepAll() throws InterpreterException
    {
        threadsExecutor = Executors.newFixedThreadPool(2);

        this.updateHeap();
        this.oneStepForAllPrograms(programsRepository.getAllPrograms());
        programsRepository.setProgramsList(removeCompletedPrograms(programsRepository.getAllPrograms()));

        threadsExecutor.shutdownNow();
    }

    /**
     * Creates a list of Callables for executing one statement in each program state.
     *
     * @param allPrograms List of program states.
     * @return List of Callables, each representing the execution of one statement in a program state.
     */
    private List<Callable<ProgramState>> createListOfCallables(List<ProgramState> allPrograms)
    {
        return allPrograms.stream()
                        .map((ProgramState program) -> (Callable<ProgramState>) (program::executeOneStatement))
                        .collect(Collectors.toList());
    }

    /**
     * Executes one step for each program in the provided list of Callables concurrently using a thread pool.
     *
     * @param callList List of Callables representing the execution of one statement in each program state.
     * @return List of Pair objects containing the updated program state or any thrown InterpreterException.
     */
    private List<Pair> executeOneStepForEachProgram(List<Callable<ProgramState>> callList)
    {
        List<Pair> newProgramsList = null;

        try {
            newProgramsList = threadsExecutor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return new Pair(future.get(), null);
                        }
                        catch(InterruptedException | ExecutionException e)
                        {
                            if (e.getCause() instanceof InterpreterException)
                                return new Pair(null, (InterpreterException) e.getCause());

                            System.out.println(e.getMessage());
                            System.exit(1);
                            return null;
                        }
                    })
                    .filter(pair -> pair.program != null || pair.thrownException != null)
                    .collect(Collectors.toList());
        }
        catch (InterruptedException e) {
            System.exit(1);
        }

        return newProgramsList;
    }

    /**
     * Executes one step for each program in the provided list of program states.
     * Each program is executed concurrently using a thread pool.
     *
     * @param allPrograms List of program states to execute one step for.
     * @throws InterpreterException if an error occurs during program execution.
     */
    public void oneStepForAllPrograms(List<ProgramState> allPrograms) throws InterpreterException
    {
        List<Callable<ProgramState>> callList = this.createListOfCallables(allPrograms);

        List<Pair> newProgramsList = this.executeOneStepForEachProgram(callList);

        for (Pair error : newProgramsList)
            if (error.thrownException != null)
                throw error.thrownException;

        allPrograms.addAll(newProgramsList.stream().map(pair -> pair.program).collect(Collectors.toList()));
        programsRepository.setProgramsList(allPrograms);

        allPrograms.forEach(this.programsRepository::logProgramState);
    }

    /**
     * Removes completed programs from the provided list.
     *
     * @param allPrograms List of program states.
     * @return List of program states with completed programs removed.
     */
    List<ProgramState> removeCompletedPrograms(List<ProgramState> allPrograms)
    {
        this.copyProgram = allPrograms.getFirst();

        return allPrograms.stream()
                .filter(program -> program.isNotCompleted())
                .collect(Collectors.toList());
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
        ProgramState firstProgram = this.programsRepository.getAllPrograms().get(0);

        firstProgram.getHeapTable().setContent(
                this.garbageCollector(
                        this.getAllUsedAddresses(
                                this.programsRepository.getAllPrograms().stream()
                                        .map(program -> program.getSymbolTable().getContent().values())
                                        .collect(Collectors.toList()),
                                firstProgram.getHeapTable().getContent()
                        ),
                        firstProgram.getHeapTable().getContent()
                ));
    }

    /**
     *
     * @param symbolTableValues all values from the symbol table
     * @param heapTable current program heap table
     * @return list of all used address from heap table
     */
    private List<Integer> getAllUsedAddresses(List<Collection<IValue>> symbolTableValues, Map<Integer, IValue> heapTable)
    {
        List<Integer> allAddresses = new ArrayList<>();

        symbolTableValues.forEach(symbolTable -> symbolTable.stream()
                .filter(value -> value instanceof ReferenceValue)
                .forEach( value -> {
                    while (value instanceof ReferenceValue) {
                        allAddresses.add(((ReferenceValue) value).getHeapAddress());
                        value = heapTable.get(((ReferenceValue) value).getHeapAddress());
                    }
                })
        );

        return allAddresses;
    }
}
