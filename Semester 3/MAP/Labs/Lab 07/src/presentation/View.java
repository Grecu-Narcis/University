package presentation;

import business.Controller;
import infrastructure.IRepository;
import infrastructure.ProgramsRepository;
import models.ProgramState;
import models.statements.IStatement;
import presentation.command.ExitCommand;
import presentation.command.RunCommand;

import java.util.Scanner;

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
