package presentation;

import business.Controller;
import exceptions.ExpressionEvaluationException;
import exceptions.StatementException;
import models.*;
import models.expressions.ArithmeticExpression;
import models.expressions.LogicExpression;
import models.expressions.ValueExpression;
import models.expressions.VariableExpression;
import models.statements.*;
import models.types.BoolType;
import models.types.BoolValue;
import models.types.IntType;
import models.types.IntValue;
import models.utils.MyDictionary;
import models.utils.MyList;
import models.utils.MyStack;

import java.util.Scanner;

public class View {
    private final Controller interpreterController;
    private final Scanner consoleScanner;
    private boolean displayFlag;


    public View(Controller ctrl)
    {
        interpreterController = ctrl;
        consoleScanner = new Scanner(System.in);
    }

    public void example1()
    {
        IStatement firstProgram = new CompoundStatement(
                new VariableDeclarationStatement("v", new BoolType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new IntType()),
                                new NOPStatement()))
        );

        PrgState program = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), firstProgram);

        interpreterController.addProgram(program);
    }

    public void example2()
    {
        IStatement secondProgram = new CompoundStatement
                (
                new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement
                        (
                        new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement
                                (
                                new AssignStatement("a",
                                        new ArithmeticExpression('+',
                                        new ValueExpression(new IntValue(2)),
                                                new ArithmeticExpression('*',
                                                        new ValueExpression(new IntValue(3)),
                                                        new ValueExpression(new IntValue(5)))
                                        )
                                ),
                                new CompoundStatement(
                                        new AssignStatement("b",
                                                new ArithmeticExpression('+',
                                                        new VariableExpression("a"),
                                                        new ValueExpression(new IntValue(1))
                                                )
                                        ),
                                        new PrintStatement(new VariableExpression("b"))
                                )
                            )
                        )
                );

        PrgState program = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), secondProgram);

        interpreterController.addProgram(program);
    }

    public void example3()
    {
        IStatement thirdProgram =
                new CompoundStatement(
                        new VariableDeclarationStatement("a", new BoolType()),
                        new CompoundStatement(
                            new VariableDeclarationStatement("v", new IntType()),
                            new CompoundStatement(
                                new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(
                                        new IfStatement(
                                            new VariableExpression("a"),
                                                new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                                new AssignStatement("v", new ValueExpression(new IntValue(3)))
                                        ),
                                        new PrintStatement(
                                                new VariableExpression("v")
                                        )
                                )
                            )
                        )
                );

        PrgState program = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), thirdProgram);

        interpreterController.addProgram(program);
    }


    private void runProgram() throws ExpressionEvaluationException, StatementException {
        PrgState program = interpreterController.getCurrentProgram();

        if (!displayFlag) {
            interpreterController.executeAllStatements();
            System.out.println(program);
            return;
        }

        System.out.println(program);
        while (!interpreterController.isEmpty()) {
            interpreterController.executeOneStatement(program);
            System.out.println(program);
        }
    }


    public void mainMenu()
    {
        String option;

        while (true) {
            try {
                System.out.println("Press 1 to enable display flag, 0 otherwise.");
                option = consoleScanner.nextLine();

                displayFlag = option.equals("1");


                System.out.println("Press 1 for the first example.");
                System.out.println("Press 2 for the second example.");
                System.out.println("Press 3 for the third example.");
                System.out.println("Press 4 to exit.");

                option = consoleScanner.nextLine();

                switch (option) {
                    case "1":
                        this.example1();
                        break;

                    case "2":
                        this.example2();
                        break;

                    case "3":
                        this.example3();
                        break;

                    case "4":
                        return;

                    default:
                        System.out.println("Please choose a valid option!");
                }

                this.runProgram();
            }

            catch (ExpressionEvaluationException | StatementException e)
            {
                System.out.println(e.getMessage());
            }
        }
    }
}
