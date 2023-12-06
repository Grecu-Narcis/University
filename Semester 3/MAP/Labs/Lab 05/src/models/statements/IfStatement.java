package models.statements;

import exceptions.InterpreterException;
import models.*;
import models.expressions.IExpression;
import models.types.BoolType;
import models.values.BoolValue;
import models.values.IValue;
import models.adts.MyIStack;

public class IfStatement implements IStatement {
    private final IExpression expressionToEvaluate;
    private final IStatement firstStatement, secondStatement;

    public IfStatement(IExpression expressionToEvaluate, IStatement firstStatement, IStatement secondStatement)
    {
        this.expressionToEvaluate = expressionToEvaluate;
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }


    /**
     * Executes an IfStatement, pushing either the firstStatement or the secondStatement onto the execution stack
     * based on the result of evaluating the expressionToEvaluate.
     *
     * @param currentState The current program state.
     * @return The updated program state after executing the if statement.
     * @throws InterpreterException If the expressionToEvaluate does not evaluate to a boolean.
     */
    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIStack<IStatement> exeStack = currentState.getStack();

        // Evaluate the expressionToEvaluate to obtain the condition value
        IValue conditionToEvaluate = expressionToEvaluate.evaluate(
                currentState.getSymbolTable(),
                currentState.getHeapTable());


        // Check if the expressionToEvaluate evaluates to a boolean
        if (!conditionToEvaluate.getType().equals(new BoolType()))
            throw new InterpreterException("Conditional expression is not boolean!");

        BoolValue conditionValue = (BoolValue) conditionToEvaluate;

        // Push either the firstStatement or the secondStatement onto the execution stack based on the condition value
        if (conditionValue.getValue())
            exeStack.push(firstStatement);
        else
            exeStack.push(secondStatement);

        return null;
    }

    @Override
    public String toString() {
        return "if " + expressionToEvaluate + " then " + firstStatement
                + " else " + secondStatement;
    }
}
