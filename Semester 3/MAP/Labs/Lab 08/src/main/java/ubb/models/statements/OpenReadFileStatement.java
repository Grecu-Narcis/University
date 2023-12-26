package ubb.models.statements;

import ubb.exceptions.InterpreterException;
import ubb.models.ProgramState;
import ubb.models.expressions.IExpression;
import ubb.models.types.Type;
import ubb.models.values.IValue;
import ubb.models.types.StringType;
import ubb.models.values.StringValue;
import ubb.models.adts.MyIDictionary;
import ubb.models.adts.MyIHeap;

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

        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable, currentState.getId());

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " - ";

        if (!fileNameValue.getType().equals(new StringType()))
            throw new InterpreterException(errorThreadIdentifier +
                    fileNameExpression + " does not evaluate to a StringValue");

        StringValue fileName = (StringValue) fileNameValue;

        // Check if the file is already opened
        if (fileTable.isDefined(fileName.getValue()))
            throw new InterpreterException(errorThreadIdentifier +
                    fileName.getValue() + " is already opened!");

        // Open the file for reading and add the BufferedReader to the file table
        try {
            BufferedReader openedFile = new BufferedReader(new FileReader(fileName.getValue()));
            fileTable.put(fileName.getValue(), openedFile);
        }

        catch (IOException e)
        {
            throw new InterpreterException(errorThreadIdentifier +
                    "Failed to open file " + fileName.getValue());
        }

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!fileNameExpression.typeCheck(typeTable).equals(new StringType()))
            throw new InterpreterException("File name is not of type string!");

        return typeTable;
    }

    @Override
    public String toString() {
        return "OpenReadFile(" + fileNameExpression + ")";
    }
}
