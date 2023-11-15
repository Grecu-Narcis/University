package models;

public class Apple implements Item {
    private float weight; // by default it's package

    public Apple(float weight)
    {
        this.weight = weight;
    }

    public Apple()
    {
        this(0);
    }
    @Override
    public float getWeight()
    {
        return weight;
    }
}
