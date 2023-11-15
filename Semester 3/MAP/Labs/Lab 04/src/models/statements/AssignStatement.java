package models.statements;

import exceptions.ExpressionEvaluationException;
import models.types.IValue;
import models.utils.MyIDictionary;
import models.PrgState;
import models.expressions.IExpression;

public class AssignStatement implements IStatement {
    private final String variableId;
    private final IExpression expressionToAssign;

    public AssignStatement(String variableId, IExpression expressionToAssign)
    {
        this.variableId = variableId;
        this.expressionToAssign = expressionToAssign;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();

        if (!symbolTable.isDefined(variableId))
            throw new ExpressionEvaluationException("Variable " + variableId + " is not defined!");

        IValue valueToAssign = expressionToAssign.evaluate(symbolTable);

        IValue variableValue = symbolTable.get(variableId);

        if (!valueToAssign.getType().equals(variableValue.getType()))
            throw new ExpressionEvaluationException("Type of variable do not match type of expression!");

        symbolTable.update(variableId, valueToAssign);

        return currentState;
    }

    @Override
    public String toString() {
        return variableId + "=" + expressionToAssign;
    }
}
