package models.statements;

import exceptions.InterpreterException;
import models.ProgramState;
import models.expressions.IExpression;
import models.values.IValue;
import models.types.StringType;
import models.values.StringValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenReadFileStatement implements IStatement {
    private final IExpression fileNameExpression;

    public OpenReadFileStatement(IExpression fileNameExpression)
    {
        this.fileNameExpression = fileNameExpression;
    }


    /**
     * Executes an OpenReadFileStatement, opening a file for reading and adding the BufferedReader
     * associated with the file to the file table.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the open read file statement.
     * @throws InterpreterException If the fileNameExpression does not evaluate to a StringType.
     * @throws InterpreterException          If the file is already opened or if an error occurs during file opening.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIDictionary<String, BufferedReader> fileTable = currentState.getFileTable();
        MyIHeap heapTable = currentState.getHeapTable();

        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable);


        if (!fileNameValue.getType().equals(new StringType()))
            throw new InterpreterException(fileNameExpression + " does not evaluate to a StringValue");

        StringValue fileName = (StringValue) fileNameValue;

        // Check if the file is already opened
        if (fileTable.isDefined(fileName.getValue()))
            throw new InterpreterException(fileName.getValue() + " is already opened!");

        // Open the file for reading and add the BufferedReader to the file table
        try {
            BufferedReader openedFile = new BufferedReader(new FileReader(fileName.getValue()));
            fileTable.put(fileName.getValue(), openedFile);
        }

        catch (IOException e)
        {
            throw new InterpreterException("Failed to open file " + fileName.getValue());
        }

        return null;
    }

    @Override
    public String toString() {
        return "OpenReadFile(" + fileNameExpression + ")";
    }
}
