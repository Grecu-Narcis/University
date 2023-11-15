package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.PrgState;

public interface IStatement {
    PrgState execute(PrgState currentState) throws ExpressionEvaluationException, InterpreterException;
}
