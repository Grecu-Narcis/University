package ubb.mppbackend.models.car;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.*;
import ubb.mppbackend.dto.CarDTO;
import ubb.mppbackend.models.user.User;

/**
 * Represents a car entity with details such as brand, model, year, price, etc.
 * This entity is mapped to the "cars" table in the database.
 */
@Getter
@Setter
@ToString
@EqualsAndHashCode
@NoArgsConstructor
@Entity(name = "cars")
public class Car {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", updatable = false)
    private Long id;

    @Column(name = "brand", nullable = false, length = 50)
    private String brand;

    @Column(name = "model", nullable = false, length = 50)
    private String model;

    @Column(name = "year", nullable = false)
    private int year;

    @Column(name = "price", nullable = false)
    private double price;

    @Column(name = "picture_url", nullable = false, columnDefinition = "TEXT")
    private String pictureUrl;

    @Column(name = "mileage", nullable = false)
    private int mileage;

    @Column(name = "fuel_type", nullable = false, length = 50)
    private String fuelType;

    @ManyToOne
    @JoinColumn(name = "owner_id", nullable = false)
    @JsonIgnore
    private User owner;

    /**
     * Constructs a new car with the specified details.
     *
     * @param brand      The brand of the car.
     * @param model      The model of the car.
     * @param year       The manufacturing year of the car.
     * @param price      The price of the car.
     * @param pictureUrl The URL to the picture of the car.
     * @param mileage    The mileage of the car.
     * @param fuelType   The fuel type of the car.
     */
    public Car(String brand, String model, int year, double price, String pictureUrl, int mileage, String fuelType) {
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.price = price;
        this.pictureUrl = pictureUrl;
        this.mileage = mileage;
        this.fuelType = fuelType;
    }

    /**
     * Constructs a new car with the specified details and owner.
     *
     * @param brand      The brand of the car.
     * @param model      The model of the car.
     * @param year       The manufacturing year of the car.
     * @param price      The price of the car.
     * @param pictureUrl The URL to the picture of the car.
     * @param mileage    The mileage of the car.
     * @param fuelType   The fuel type of the car.
     * @param owner      The owner of the car.
     */
    public Car(String brand, String model, int year, double price, String pictureUrl, int mileage, String fuelType, User owner) {
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.price = price;
        this.pictureUrl = pictureUrl;
        this.mileage = mileage;
        this.fuelType = fuelType;
        this.owner = owner;
    }

    public Car(CarDTO carDTO) {
        this.brand = carDTO.getBrand();
        this.model = carDTO.getModel();
        this.mileage = carDTO.getMileage();
        this.fuelType = carDTO.getFuelType();
        this.year = carDTO.getYear();
        this.price = carDTO.getPrice();
        this.pictureUrl = "default.png";
    }
}
