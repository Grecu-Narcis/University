package models;

public class Car extends Vehicle {
    public Car(String color, String brand)
    {
        this.color = color;
        this.brand = brand;
    }

    @Override
    public String getType()
    {
        return "Car";
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Car other))
            return false;

        return this.getBrand().equals(other.getBrand()) && this.getColor().equals(other.getColor());
    }
}

