package ubb.models.values;

import ubb.models.types.IntType;
import ubb.models.types.Type;

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
    public boolean equals(Object obj) {
        if (! (obj instanceof IntValue))
            return false;

        IntValue objValue = (IntValue) obj;
        return this.getValue() == objValue.getValue();
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
