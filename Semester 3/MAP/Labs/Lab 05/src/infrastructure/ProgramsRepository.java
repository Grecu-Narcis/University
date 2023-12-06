package infrastructure;

import models.ProgramState;
import models.statements.IStatement;
import models.values.IValue;
import models.adts.MyIDictionary;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ProgramsRepository implements IRepository {
    private ProgramState program;
    private final String logFilePath;

    public ProgramsRepository(String logFilePath) {
        this.logFilePath = logFilePath;

        // clear the log file
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath)));
            logFile.close();
        }
        catch (IOException ignored)
        {

        }
    }

    @SuppressWarnings("unused")
    public ProgramsRepository(ProgramState program, String logFilePath)
    {
        this.program = program;
        this.logFilePath = logFilePath;
    }

    @Override
    public void addProgram(ProgramState programToAdd) {
        this.program = programToAdd;
    }

    @Override
    public ProgramState getCurrentProgram() {
        return program;
    }

    private void logExeStack(PrintWriter logFile) {
        logFile.println("ExeStack:");

        ArrayList<IStatement> stackStatements = (ArrayList<IStatement>) this.getCurrentProgram().getStackStatements();

        for (IStatement currentStatement : stackStatements)
            logFile.println(currentStatement.toString());

        logFile.println();
    }

    private void logSymbolTable(PrintWriter logFile)
    {
        logFile.println("SymTable:");

        MyIDictionary<String, IValue> symbolTable = this.getCurrentProgram().getSymbolTable();
        for (String key : symbolTable.getKeySet())
            logFile.println(key + " = " + symbolTable.get(key));

        logFile.println();
    }

    private void logOutput(PrintWriter logFile)
    {
        logFile.println("Output:");

        List<IValue> outputList = this.getCurrentProgram().getOutputList().getOutput();
        for (IValue currentValue : outputList)
            logFile.println(currentValue);

        logFile.println();
    }

    private void logFileTable(PrintWriter logFile)
    {
        logFile.println("File Table:");

        MyIDictionary<String, BufferedReader> fileTable = this.getCurrentProgram().getFileTable();
        for (String fileName : fileTable.getKeySet())
            logFile.println(fileName);

        logFile.println();
    }

    @Override
    public void logProgramState() throws IOException {
        PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));

        // LOG Exe Stack
        this.logExeStack(logFile);

        // LOG Symbol Table
        this.logSymbolTable(logFile);

        // LOG Output
        this.logOutput(logFile);

        // LOG File Table
        this.logFileTable(logFile);

        logFile.close();
    }


}
