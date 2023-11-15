package models;

import models.statements.CompoundStatement;
import models.statements.IStatement;
import models.types.IValue;
import models.utils.*;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class PrgState {
    private MyIStack<IStatement> exeStack;
    private MyIDictionary<String, IValue> symbolTable;
    private MyIList<IValue> outputList;
    private final MyIDictionary<String, BufferedReader> fileTable;

    public PrgState(IStatement program) {
        this.exeStack = new MyStack<>();
        this.symbolTable = new MyDictionary<>();
        this.outputList = new MyList<>();
        this.fileTable = new MyDictionary<>();

        this.exeStack.push(program);
    }

    public MyIStack<IStatement> getStack()
    {
        return this.exeStack;
    }

    public void setExeStack(MyIStack<IStatement> newStack)
    {
        this.exeStack = newStack;
    }

    public MyIDictionary<String, IValue> getSymbolTable()
    {
        return this.symbolTable;
    }

    public void setSymbolTable(MyIDictionary<String, IValue> newSymbolTable)
    {
        this.symbolTable = newSymbolTable;
    }

    public MyIList<IValue> getOutputList()
    {
        return this.outputList;
    }

    public MyIDictionary<String, BufferedReader> getFileTable()
    {
        return this.fileTable;
    }
    public void setOutputList(MyList<IValue> newOutputList)
    {
        this.outputList = newOutputList;
    }

    public List<IStatement> getStackStatements() {
        ArrayList<IStatement> stackStatements = new ArrayList<>();

        if (exeStack.isEmpty())
            return stackStatements;

        Stack<IStatement> statements = new Stack<>();
        for (IStatement currentStatement : this.exeStack.getStackAsList())
            statements.push(currentStatement);

        while (!statements.isEmpty())
        {
            IStatement topStatement = statements.pop();
            if (topStatement instanceof CompoundStatement currentStatement)
            {
                statements.push(currentStatement.getSecondStatement());
                statements.push(currentStatement.getFirstStatement());
            }

            else
                stackStatements.add(topStatement);
        }

        return stackStatements;
    }

    @Override
    public String toString() {
        return "PrgState{" +
                "exeStack=" + exeStack +
                ", symbolTable=" + symbolTable +
                ", outputList=" + outputList +
                ", FileTable=" + fileTable +
                '}';
    }
}
