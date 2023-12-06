package models.expressions;


import exceptions.InterpreterException;
import models.types.BoolType;
import models.values.BoolValue;
import models.values.IValue;
import models.adts.MyIDictionary;
import models.adts.MyIHeap;

public class LogicExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final String operation;

    public LogicExpression(IExpression firstExpression, IExpression secondExpression, String operation)
    {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    /**
     * Evaluates a boolean expression involving two boolean operands and a logical operator.
     *
     * @param symbolTable The symbol table containing variable bindings.
     * @param heapTable   The heap table containing memory allocations.
     * @return A BoolValue representing the result of the boolean expression.
     * @throws InterpreterException If the operands are not booleans or if an invalid logical operator is used.
     */
    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws InterpreterException {
        IValue firstValue = firstExpression.evaluate(symbolTable, heapTable);
        IValue secondValue = secondExpression.evaluate(symbolTable, heapTable);

        // check if both operands are of type boolean
        if (!firstValue.getType().equals(new BoolType()))
            throw new InterpreterException("First operand is not bool!");

        if (!secondValue.getType().equals(new BoolType()))
            throw new InterpreterException("Second operand is not bool!");

        BoolValue firstOperand = (BoolValue) firstValue;
        BoolValue secondOperand = (BoolValue) secondValue;

        // perform the corresponding logical operation
        switch (operation)
        {
            case "&&": // LOGIC AND
                return new BoolValue(firstOperand.getValue() && secondOperand.getValue());

            case "||": // LOGIC OR
                return new BoolValue(firstOperand.getValue() || secondOperand.getValue());
        }

        return null;
    }

    @Override
    public String toString() {
        return firstExpression.toString() + operation + secondExpression.toString();
    }
}
