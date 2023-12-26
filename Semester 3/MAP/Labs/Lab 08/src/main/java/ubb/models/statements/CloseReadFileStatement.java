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
import java.io.IOException;


public class CloseReadFileStatement implements IStatement {
    private final IExpression fileNameExpression;

    public CloseReadFileStatement(IExpression fileNameExpression)
    {
        this.fileNameExpression = fileNameExpression;
    }


    /**
     * Executes a CloseReadFileStatement, closing the BufferedReader associated with the file specified
     * by the result of evaluating the fileNameExpression, and removing it from the file table.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the close file statement.
     * @throws InterpreterException If the fileNameExpression does not evaluate to a StringType.
     * @throws InterpreterException          If the file is not opened or if an error occurs during file closing.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();
        MyIDictionary<String, BufferedReader> fileTable = currentState.getFileTable();

        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable, currentState.getId());

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " - ";

        if (!fileNameValue.getType().equals(new StringType()))
            throw new InterpreterException(errorThreadIdentifier
                    + fileNameExpression + " does not evaluate to a StringType!");

        StringValue fileName = (StringValue) fileNameValue;

        // Check if the file is opened in the file table
        if (!fileTable.isDefined(fileName.getValue()))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("File %s is not opened!", fileName));

        // Get the BufferedReader associated with the file name
        BufferedReader fileToClose = fileTable.get(fileName.getValue());

        try {
            // Close the file and remove it from the file table
            fileToClose.close();
            fileTable.remove(fileName.getValue());
        }

        catch (IOException e)
        {
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("Failed to close file %s!", fileName.getValue()));
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
        return String.format("CloseFile(%s)", this.fileNameExpression);
    }
}
