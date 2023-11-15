package presentation.command;

import business.Controller;
import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;

import java.io.IOException;

public class RunCommand extends Command {
    private final Controller interpreterController;

    public RunCommand(String key, String description, Controller interpreterController)
    {
        super(key, description);
        this.interpreterController = interpreterController;
    }

    @Override
    public void execute()
    {
        try
        {
            interpreterController.executeAllStatements();

        }

        catch (IOException | ExpressionEvaluationException | InterpreterException e)
        {
            System.out.println(e.getMessage());
        }
    }
}
