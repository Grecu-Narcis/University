package ubb.presentation.cli;

import ubb.models.statements.IStatement;
import ubb.presentation.Examples;
import ubb.presentation.cli.TextMenu;
import ubb.presentation.command.ExitCommand;
import ubb.presentation.command.RunCommand;

public class View {
    public void mainMenu()
    {
        TextMenu menu = new TextMenu();

        menu.addCommand(new ExitCommand("0", "exit"));

        int commandIndex = 1;

        for (IStatement currentStatement : Examples.getAllExamples())
        {
            menu.addCommand(new RunCommand(Integer.toString(commandIndex), currentStatement));
            commandIndex++;
        }

        menu.show();
    }
}
