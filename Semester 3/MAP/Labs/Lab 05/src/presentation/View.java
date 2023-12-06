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
    private final Scanner consoleScanner;
    private boolean displayFlag;


    public View()
    {
        consoleScanner = new Scanner(System.in);
    }



    public void mainMenu()
    {
        TextMenu menu = new TextMenu();

        menu.addCommand(new ExitCommand("0", "exit"));

        int commandIndex = 1;

        for (IStatement currentStatement : Examples.getAllExamples())
        {
            ProgramState currentProgram = new ProgramState(currentStatement);
            IRepository repository = new ProgramsRepository("log.txt");
            Controller controller = new Controller(repository);
            controller.addProgram(currentProgram);

            menu.addCommand(new RunCommand(Integer.toString(commandIndex), currentStatement.toString(), controller));
            commandIndex++;
        }

        menu.show();
    }
}
