package presentation;

import models.expressions.*;
import models.statements.*;
import models.types.*;
import models.values.BoolValue;
import models.values.IntValue;
import models.values.StringValue;

import java.util.ArrayList;
import java.util.List;

public class Examples {
    public static IStatement createExample1() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new BoolType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new IntType()),
                                new NOPStatement()))
        );
    }

    public static IStatement createExample2()
    {
        return new CompoundStatement
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
    }

    public static IStatement createExample3()
    {
        return new CompoundStatement(
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
    }

    public static IStatement createExample4() {
        return new CompoundStatement(
                        new VariableDeclarationStatement("varf", new StringType()),
                        new CompoundStatement(
                                new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                                new CompoundStatement(
                                        new OpenReadFileStatement(new VariableExpression("varf")),
                                        new CompoundStatement(
                                                new VariableDeclarationStatement("varc", new IntType()),
                                                new CompoundStatement(
                                                        new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                        new CompoundStatement(
                                                                new PrintStatement(new VariableExpression("varc")),
                                                                new CompoundStatement(
                                                                        new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new VariableExpression("varc")),
                                                                                new CloseReadFileStatement(new VariableExpression("varf"))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );
    }

    public static IStatement createExample5() {
        return new CompoundStatement(
            new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
            new CompoundStatement(
                new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(
                    new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                    new CompoundStatement(
                        new AllocateStatement("a", new VariableExpression("v")),
                        new CompoundStatement(
                            new PrintStatement(new VariableExpression("v")),
                            new PrintStatement(new VariableExpression("a"))
                        )
                    )
                )
            )
        );
    }

    public static IStatement createExample6()
    {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(
                                        new AllocateStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression('+',
                                                        new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))),
                                                        new ValueExpression(new IntValue(5))
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement createExample7()
    {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompoundStatement(
                                        new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression(
                                                '+',
                                                new ReadHeapExpression(new VariableExpression("v")),
                                                new ValueExpression(new IntValue(5))
                                                ))
                                )
                        )
                )
        );
    }

    public static IStatement createExample8()
    {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(
                                        new AllocateStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new AllocateStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(
                                                        new ReadHeapExpression(new VariableExpression("a"))
                                                ))
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement createExample9()
    {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType() ),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(5))),
                        new CompoundStatement(
                                new WhileStatement(
                                        new RelationalExpression(
                                                new VariableExpression("v"),
                                                new ValueExpression(new IntValue(0)),
                                                ">"
                                        ),
                                        new CompoundStatement(
                                                new PrintStatement(new VariableExpression("v")),
                                                new AssignStatement("v", new ArithmeticExpression(
                                                        '-',
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(1))
                                                ))
                                        )
                                ),
                                new PrintStatement(new VariableExpression("v"))
                        )
                )
        );
    }


    public static List<IStatement> getAllExamples()
    {
        ArrayList<IStatement> allStatements = new ArrayList<>();

        allStatements.add(createExample1());
        allStatements.add(createExample2());
        allStatements.add(createExample3());
        allStatements.add(createExample4());
        allStatements.add(createExample5());
        allStatements.add(createExample6());
        allStatements.add(createExample7());
        allStatements.add(createExample8());
        allStatements.add(createExample9());

        return allStatements;
    }
}
