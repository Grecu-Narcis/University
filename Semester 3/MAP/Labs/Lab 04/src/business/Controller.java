package business;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import exceptions.StackException;
import infrastructure.IRepository;
import models.statements.IStatement;
import models.utils.MyIStack;
import models.PrgState;

import java.io.IOException;

public class Controller {
    private final IRepository programsRepository;

    public Controller(IRepository programs)
    {
        this.programsRepository = programs;
    }

    public void addProgram(PrgState programToAdd)
    {
        programsRepository.addProgram(programToAdd);
    }

    public PrgState getCurrentProgram()
    {
        return programsRepository.getCurrentProgram();
    }

    public boolean isEmpty()
    {
        return this.programsRepository.getCurrentProgram().getStack().isEmpty();
    }

    public PrgState executeOneStatement(PrgState currentState) throws ExpressionEvaluationException, InterpreterException {
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

    public void executeAllStatements() throws ExpressionEvaluationException, IOException, InterpreterException
    {
        PrgState currentState = programsRepository.getCurrentProgram();

        while (!currentState.getStack().isEmpty())
        {
            this.executeOneStatement(currentState);
            this.programsRepository.logProgramState();
        }
    }
}
