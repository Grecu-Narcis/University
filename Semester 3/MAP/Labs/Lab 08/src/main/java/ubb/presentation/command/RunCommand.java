package ubb.presentation.command;

import ubb.business.InterpreterController;
import ubb.exceptions.InterpreterException;
import ubb.infrastructure.IRepository;
import ubb.infrastructure.ProgramsRepository;
import ubb.models.ProgramState;
import ubb.models.adts.MyDictionary;
import ubb.models.statements.IStatement;

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
        InterpreterController interpreterController = new InterpreterController(repository);
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
