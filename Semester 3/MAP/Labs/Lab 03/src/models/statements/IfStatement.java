package models.statements;

import exceptions.ExpressionEvaluationException;
import models.*;
import models.expressions.IExpression;
import models.types.BoolType;
import models.types.BoolValue;
import models.types.IValue;
import models.utils.MyIStack;

public class IfStatement implements IStatement {
    private final IExpression expressionToEvaluate;
    private final IStatement firstStatement, secondStatement;

    public IfStatement(IExpression expressionToEvaluate, IStatement firstStatement, IStatement secondStatement)
    {
        this.expressionToEvaluate = expressionToEvaluate;
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIStack<IStatement> exeStack = currentState.getStack();

        IValue conditionToEvaluate = expressionToEvaluate.evaluate(currentState.getSymbolTable());

        if (!conditionToEvaluate.getType().equals(new BoolType()))
            throw new ExpressionEvaluationException("Conditional expression is not boolean!");

        BoolValue conditionValue = (BoolValue) conditionToEvaluate;

        if (conditionValue.getValue())
            exeStack.push(firstStatement);
        else
            exeStack.push(secondStatement);

        return currentState;
    }

    @Override
    public String toString() {
        return "(if " + expressionToEvaluate + " then " + firstStatement
                + " else " + secondStatement + ")";
    }
}
