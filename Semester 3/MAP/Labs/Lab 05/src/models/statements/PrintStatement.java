package models.statements;

import exceptions.InterpreterException;
import models.values.IValue;
import models.adts.MyIList;
import models.ProgramState;
import models.expressions.IExpression;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression)
    {
        this.expression = expression;
    }

    /**
     * Executes a PrintStatement, adding the result of evaluating the expression to the output list.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the print statement.
     * @throws InterpreterException If there is an error during expression evaluation.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIList<IValue> outputList = currentState.getOutputList();

        outputList.add(expression.evaluate(
                currentState.getSymbolTable(),
                currentState.getHeapTable())
        );

        return null;
    }

    @Override
    public String toString() {
        return "print(" + expression + ")";
    }
}
