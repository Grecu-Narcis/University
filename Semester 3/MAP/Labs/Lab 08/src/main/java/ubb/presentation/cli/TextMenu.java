package ubb.presentation.cli;

import ubb.models.adts.MyDictionary;
import ubb.models.adts.MyIDictionary;
import ubb.presentation.command.Command;

import java.util.ArrayList;
import java.util.Scanner;

public class TextMenu {
    private final MyIDictionary<String, Command> commands;

    public TextMenu()
    {
        commands = new MyDictionary<>();
    }

    public void addCommand(Command commandToAdd)
    {
        commands.put(commandToAdd.getKey(), commandToAdd);
    }

    private void printMenu()
    {
        ArrayList<String> sortedKeys = new ArrayList<>(commands.getKeySet());

        sortedKeys.sort((firstKey, secondKey) -> {
            int firstValue = Integer.parseInt(firstKey);
            int secondValue = Integer.parseInt(secondKey);

            return Integer.compare(firstValue, secondValue);
        });

        for (String commandKey : sortedKeys)
            System.out.println(commandKey + " -> " + commands.get(commandKey).getDescription());
    }

    public void show()
    {
        Scanner consoleReader = new Scanner(System.in);

        while (true)
        {
            this.printMenu();

            System.out.print("Choose an option: ");
            String option = consoleReader.nextLine();

            Command command = commands.get(option);

            if (command == null)
            {
                System.out.println("Invalid option!");
                continue;
            }

            command.execute();
        }
    }
}
