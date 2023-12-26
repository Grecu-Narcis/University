package models.statements;

import exceptions.InterpreterException;
import models.adts.MyIDictionary;
import models.adts.MyIStack;
import models.ProgramState;
import models.types.Type;

public class CompoundStatement implements IStatement {
    private final IStatement firstStatement, secondStatement;

    public CompoundStatement(IStatement firstStatement, IStatement secondStatement)
    {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    public IStatement getFirstStatement()
    {
        return this.firstStatement;
    }

    public IStatement getSecondStatement()
    {
        return this.secondStatement;
    }

    @Override
    public ProgramState execute(ProgramState currentState) throws InterpreterException {
        MyIStack<IStatement> exeStack = currentState.getStack();

        exeStack.push(secondStatement);
        exeStack.push(firstStatement);

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        // MyIDictionary<String, Type> typeEnv1 = firstStatement.typeCheck(typeEnv);
        // MyIDictionary<String, Type> typeEnv2 = firstStatement.typeCheck(typeEnv1);

        return secondStatement.typeCheck(firstStatement.typeCheck(typeTable));
    }

    @Override
    public String toString() {
        return firstStatement.toString() + "; " + secondStatement.toString();
    }
}
