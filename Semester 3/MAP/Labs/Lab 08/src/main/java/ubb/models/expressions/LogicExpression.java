package ubb.models.expressions;


import ubb.exceptions.InterpreterException;
import ubb.models.types.BoolType;
import ubb.models.types.Type;
import ubb.models.values.BoolValue;
import ubb.models.values.IValue;
import ubb.models.adts.MyIDictionary;
import ubb.models.adts.MyIHeap;

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
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable, int threadID) throws InterpreterException {
        IValue firstValue = firstExpression.evaluate(symbolTable, heapTable, threadID);
        IValue secondValue = secondExpression.evaluate(symbolTable, heapTable, threadID);

        String errorThreadIdentifier = "Thread: " + threadID + " - ";

        // check if both operands are of type boolean
        if (!firstValue.getType().equals(new BoolType()))
            throw new InterpreterException(errorThreadIdentifier +
                    "First operand is not bool!");

        if (!secondValue.getType().equals(new BoolType()))
            throw new InterpreterException(errorThreadIdentifier +
                    "Second operand is not bool!");

        BoolValue firstOperand = (BoolValue) firstValue;
        BoolValue secondOperand = (BoolValue) secondValue;

        // perform the corresponding logical operation
        return switch (operation) {
            case "&&" -> // LOGIC AND
                    new BoolValue(firstOperand.getValue() && secondOperand.getValue());
            case "||" -> // LOGIC OR
                    new BoolValue(firstOperand.getValue() || secondOperand.getValue());
            default -> null;
        };

    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type firstExpressionType = firstExpression.typeCheck(typeTable);
        Type secondExpressionType = secondExpression.typeCheck(typeTable);

        if (!firstExpressionType.equals(new BoolType()))
            throw new InterpreterException("First operand is not boolean!");

        if (!secondExpressionType.equals(new BoolType()))
            throw new InterpreterException("Second operand is not boolean!");

        return new BoolType();
    }

    @Override
    public String toString() {
        return firstExpression.toString() + operation + secondExpression.toString();
    }
}
