package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.StatementException;
import models.PrgState;

public interface IStatement {
    PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException;
}
