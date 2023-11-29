package presentation.command;

import business.Controller;
import exceptions.InterpreterException;

public class RunCommand extends Command {
    private final Controller interpreterController;

    public RunCommand(String key, String description, Controller interpreterController)
    {
        super(key, description);
        this.interpreterController = interpreterController;
    }

    @Override
    public void execute() {
        try {
            interpreterController.allSteps();
        }
        catch (InterpreterException e)
        {
            System.out.println(e.getMessage());
        }
    }
}
