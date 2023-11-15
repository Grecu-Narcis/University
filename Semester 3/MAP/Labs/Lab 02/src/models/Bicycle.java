package models;

public class Bicycle extends Vehicle {
    public Bicycle(String color, String brand)
    {
        this.color = color;
        this.brand = brand;
    }

    @Override
    public String getType()
    {
        return "Bicycle";
    }

    @Override
    public boolean equals(Object obj) {
        if (! (obj instanceof Bicycle other))
            return false;

        return this.getBrand().equals(other.getBrand()) && this.getColor().equals(other.getColor());
    }
}
