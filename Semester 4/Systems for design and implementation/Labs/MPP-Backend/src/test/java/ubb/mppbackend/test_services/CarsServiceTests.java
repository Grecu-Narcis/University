package ubb.mppbackend.test_services;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import ubb.mppbackend.business.CarsService;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.models.car.Car;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.CarsRepositoryJPA;

import java.util.List;
import java.util.Optional;

@SpringBootTest
public class CarsServiceTests {
    @MockBean
    private CarsRepositoryJPA carsRepositoryJPA;
    private CarsService carsService;

    @BeforeEach
    public void setUp() {
        this.carsService = new CarsService(carsRepositoryJPA, null);
    }

    @Test
    public void testGetCarByIdSuccess() throws Exception {
        User testUser = new User("Bogdan", "test", "test", "test");
        Car carToFind = new Car("Audi", "A4", 2018, 20000, "audi-a4.jpg", 10000, "Diesel", testUser);
        carToFind.setId((long) 1);
        Mockito.when(this.carsRepositoryJPA.findById(carToFind.getId())).thenReturn(java.util.Optional.of(carToFind));

        Long idToSearch = this.carsService.getCarById(carToFind.getId()).getId();
        Assertions.assertEquals(this.carsService.getCarById(idToSearch).getId(), idToSearch);
    }

    @Test
    public void testGetCarByIdFails() {
        Long idToSearch = (long) -1;
        Mockito.when(this.carsRepositoryJPA.findById(idToSearch)).thenReturn(java.util.Optional.empty());
        Assertions.assertThrows(RepositoryException.class, () -> this.carsService.getCarById(idToSearch));
    }

    @Test
    public void testUpdateCar() {
        User testUser = new User("Bogdan", "test", "test", "test");
        Car carToUpdate = new Car("Audi", "A4", 2018, 20000, "audi-a4.jpg", 10000, "Diesel", testUser);
        carToUpdate.setId((long) 1);

        Mockito.when(this.carsRepositoryJPA.save(carToUpdate)).thenReturn(carToUpdate);
        Mockito.when(this.carsRepositoryJPA.findById(carToUpdate.getId())).thenReturn(Optional.of(carToUpdate));
        this.carsService.updateCar(carToUpdate);

        try {
            Car updatedCar = this.carsService.getCarById(carToUpdate.getId());
            Assertions.assertEquals(updatedCar, carToUpdate);
        }
        catch (Exception e) {
            Assertions.fail();
        }
    }

    @Test
    public void testGetAllCarsByOwnerId() {
        User testUser = new User("Bogdan", "test", "test", "test");
        Car car1 = new Car("Audi", "A4", 2018, 20000, "audi-a4.jpg", 10000, "Diesel", testUser);
        Car car2 = new Car("BMW", "X6", 2019, 30000, "bmw-x6.jpg", 20000, "Gasoline", testUser);
        Car car3 = new Car("Mercedes", "C180", 2017, 15000, "mercedes-c180.jpg", 30000, "Diesel", testUser);
        Car car4 = new Car("Seat", "Ibiza", 2011, 5499, "seat-ibiza.jpg", 295345, "Diesel", testUser);
        Car car5 = new Car("Ford", "Mustang", 2015, 10000, "mustang.jpg", 40000, "Gasoline", testUser);
        Car car6 = new Car("Mazda", "Miata", 2022, 5235, "miata.jpg", 5234, "Gasoline", testUser);
        Car car7 = new Car("Volkswagen", "Golf", 2022, 30000, "golf.jpg", 20000, "Gasoline", testUser);

        Mockito.when(this.carsRepositoryJPA.findAllByOwnerId(testUser.getId())).thenReturn(List.of(car1, car2, car3, car4, car5, car6, car7));
        Assertions.assertEquals(this.carsService.getAllCarsByOwnerId(testUser.getId()).size(), 7);
    }
}
