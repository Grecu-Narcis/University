package presentation.command;

import business.Controller;
import exceptions.InterpreterException;
import infrastructure.IRepository;
import infrastructure.ProgramsRepository;
import models.ProgramState;
import models.adts.MyDictionary;
import models.statements.IStatement;

public class RunCommand extends Command {
    private final IStatement programStatement;

    public RunCommand(String key, IStatement programStatement)
    {
        super(key, programStatement.toString());
        this.programStatement = programStatement;
    }

    @Override
    public void execute() {
        try {
            programStatement.typeCheck(new MyDictionary<>());
        }
        catch (InterpreterException e)
        {
            System.out.println(e.getMessage());
            return;
        }

        ProgramState currentProgram = new ProgramState(programStatement);
        IRepository repository = new ProgramsRepository("log.txt");
        Controller interpreterController = new Controller(repository);
        interpreterController.addProgram(currentProgram);

        try {
            interpreterController.allSteps();
        }
        catch (InterpreterException e)
        {
            System.out.println(e.getMessage());
        }
    }
}
