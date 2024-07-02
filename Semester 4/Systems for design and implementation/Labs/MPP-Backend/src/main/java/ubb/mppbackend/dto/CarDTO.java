package ubb.mppbackend.dto;


import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class CarDTO {
    private String brand;
    private String model;
    private int mileage;
    private String fuelType;
    private int year;
    private double price;
    private Long ownerId;
}
