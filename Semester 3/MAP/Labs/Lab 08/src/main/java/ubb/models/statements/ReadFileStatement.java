package ubb.models.statements;

import ubb.exceptions.InterpreterException;
import ubb.models.ProgramState;
import ubb.models.expressions.IExpression;
import ubb.models.types.*;
import ubb.models.adts.MyIDictionary;
import ubb.models.adts.MyIHeap;
import ubb.models.types.IntType;
import ubb.models.types.StringType;
import ubb.models.types.Type;
import ubb.models.values.IValue;
import ubb.models.values.IntValue;
import ubb.models.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private final IExpression fileNameExpression;
    private final String variableId;

    public ReadFileStatement(IExpression fileNameExpression, String variableId)
    {
        this.fileNameExpression = fileNameExpression;
        this.variableId = variableId;
    }

    /**
     * Executes a ReadFileStatement, reading a line from the BufferedReader associated with the file specified
     * by the result of evaluating the fileNameExpression, and updating the value of the specified variable with
     * the read integer value.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the read file statement.
     * @throws InterpreterException If the variable is not defined or does not evaluate to IntType,
     *                                       or if the fileNameExpression does not evaluate to a StringType.
     * @throws InterpreterException          If the file is not opened or if an error occurs during file reading.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIDictionary<String, BufferedReader> fileTable = currentState.getFileTable();
        MyIHeap heapTable = currentState.getHeapTable();

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " - ";

        // Check if the variable to update is defined in the symbol table and evaluates to IntType
        if (!symbolTable.isDefined(variableId))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("Variable %s is not defined!", variableId));

        IValue variableValue = symbolTable.get(variableId);

        if (!variableValue.getType().equals(new IntType()))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("Variable %s does not evaluate to IntType", variableId));

        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable, currentState.getId());

        if (!fileNameValue.getType().equals(new StringType()))
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("File %s is not opened!", fileNameValue));

        StringValue fileName = (StringValue) fileNameValue;
        BufferedReader openedFile = fileTable.get(fileName.getValue());

        // Check if the file is open for read
        if (openedFile == null)
            throw new InterpreterException(errorThreadIdentifier +
                    String.format("File %s is not opened!", fileName));

        try {
            String newValue = openedFile.readLine().strip();
            int valueToAssign;

            if (newValue.isEmpty())
            {
                valueToAssign = 0;
            }
            else {
                valueToAssign = Integer.parseInt(newValue);
            }

            symbolTable.update(variableId, new IntValue(valueToAssign));
        }

        catch (IOException e)
        {
            throw new InterpreterException(errorThreadIdentifier +
                    "Failed to read from file " + fileName.getValue());
        }

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!fileNameExpression.typeCheck(typeTable).equals(new StringType()))
            throw new InterpreterException("File name is not of type string!");

        if (!typeTable.get(variableId).equals(new IntType()))
            throw  new InterpreterException("Error: Read file requires an int variable as argument!");

        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("ReadFile(%s, %s)", this.fileNameExpression, this.variableId);
    }
}
