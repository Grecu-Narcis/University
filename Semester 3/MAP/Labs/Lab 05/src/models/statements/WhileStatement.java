package models.statements;

import exceptions.InterpreterException;
import models.PrgState;
import models.expressions.IExpression;
import models.types.BoolType;
import models.values.BoolValue;
import models.values.IValue;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;
import models.utils.MyIStack;

public class WhileStatement implements IStatement {
    private final IExpression expressionToEvaluate;
    private final IStatement innerStatement;

    public WhileStatement(IExpression expressionToEvaluate, IStatement innerStatement)
    {
        this.expressionToEvaluate = expressionToEvaluate;
        this.innerStatement = innerStatement;
    }

    /**
     * Executes a WhileStatement, repeatedly pushing itself and the innerStatement onto the program stack
     * as long as the result of evaluating the expressionToEvaluate is true.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the while statement.
     * @throws InterpreterException If the expressionToEvaluate does not evaluate to a boolean.
     * @throws InterpreterException          If there is an error during expression evaluation.
     */
    @Override
    public PrgState execute(PrgState currentState) throws InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();
        MyIStack<IStatement> programStack = currentState.getStack();

        IValue evaluatedExpression = expressionToEvaluate.evaluate(symbolTable, heapTable, currentState.getId());

        String errorThreadIdentifier = "Thread: " + currentState.getId() + " - ";

        // Check if the expressionToEvaluate evaluates to a boolean
        if (!evaluatedExpression.getType().equals(new BoolType()))
            throw new InterpreterException(errorThreadIdentifier +
                    "Expression used in while statement cannot be evaluated as boolean!");

        BoolValue expressionValue = (BoolValue) evaluatedExpression;

        // If the expression is false, do not execute the innerStatement and return the current program state
        if (!expressionValue.getValue())
            return currentState;

        // Push the WhileStatement and the innerStatement onto the program stack to repeat the loop
        programStack.push(this);
        programStack.push(innerStatement);

        return null;
    }

    @Override
    public String toString() {
        return "while(" + this.expressionToEvaluate + ") {" + this.innerStatement + "}";
    }
}