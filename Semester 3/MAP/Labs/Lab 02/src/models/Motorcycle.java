package models;

public class Motorcycle extends Vehicle {
    public Motorcycle(String color, String brand)
    {
        this.color = color;
        this.brand = brand;
    }

    @Override
    public String getType()
    {
        return "Motorcycle";
    }

    @Override
    public boolean equals(Object obj) {
        if (! (obj instanceof Motorcycle other))
            return false;

        return this.getBrand().equals(other.getBrand()) && this.getColor().equals(other.getColor());
    }
}
