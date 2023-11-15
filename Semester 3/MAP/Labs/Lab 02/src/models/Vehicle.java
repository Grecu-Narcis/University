package models;

// cars, motorcycles, bicycles . print only red ones

public abstract class Vehicle {
    protected String color, brand;
    public String getColor()
    {
        return this.color;
    }
    public String getBrand()
    {
        return this.brand;
    }
    public abstract String getType();

    @Override
    public String toString()
    {
        return this.getType() + " (" + color + " " + brand + ")";
    }
}
