package models.statements;

import exceptions.ExpressionEvaluationException;
import models.types.IValue;
import models.utils.MyIList;
import models.PrgState;
import models.expressions.IExpression;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression)
    {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIList<IValue> outputList = currentState.getOutputList();

        outputList.add(expression.evaluate(currentState.getSymbolTable()));

        return currentState;
    }

    @Override
    public String toString() {
        return "print(" + expression + ")";
    }
}
