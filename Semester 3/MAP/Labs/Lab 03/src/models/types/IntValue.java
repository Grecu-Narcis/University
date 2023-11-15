package models.types;

public class IntValue implements IValue {
    private final int value;

    public IntValue(int value)
    {
        this.value = value;
    }

    public int getValue()
    {
        return value;
    }

    @Override
    public String toString()
    {
        return Integer.toString(value);
    }

    @Override
    public Type getType() {
        return new IntType();
    }
}
