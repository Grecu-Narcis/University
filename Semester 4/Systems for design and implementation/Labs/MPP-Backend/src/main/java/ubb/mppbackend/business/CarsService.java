package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import ubb.mppbackend.dto.CarDTO;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.models.car.Car;
import ubb.mppbackend.models.car.CarMockGenerator;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.CarsRepositoryJPA;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * Service responsible for cars entities
 */
@Service
public class CarsService {
    private final CarsRepositoryJPA carsRepository;
    private final UsersRepositoryJPA usersRepository;

    @Autowired
    public CarsService(CarsRepositoryJPA carsRepository, UsersRepositoryJPA usersRepository) {
        this.carsRepository = carsRepository;
        this.usersRepository = usersRepository;

//        List<User> allManagers = usersRepository.findAllByRole("MANAGER")
//            .stream()
//            .filter(user -> user.getEmail().equals("manager@gmail.com"))
//            .toList();
//        CarMockGenerator.addFakeCars(10000, allManagers, this.carsRepository);
    }

    /**
     *
     * @param id Long representing id of the car to be returned
     * @return the car with the given id
     * @throws RepositoryException if no car matches the id
     */
    public Car getCarById(Long id) throws RepositoryException {
        Optional<Car> car = carsRepository.findById(id);

        if (car.isEmpty())
            throw new RepositoryException("Car not found!");

        return car.get();
    }

    /**
     * Updates the information of the provided car. The updated car object is saved using the carsRepository.
     *
     * @param car The car object to be updated. Must not be null.
     */
    public void updateCar(Car car) {
        carsRepository.save(car);
    }

    /**
     * Retrieves all cars owned by the specified user ID.
     *
     * @param userId The unique identifier of the owner whose cars are to be retrieved.
     * @return A list of cars owned by the specified user ID.
     */
    public List<Car> getAllCarsByOwnerId(Long userId) {
        return carsRepository.findAllByOwnerId(userId);
    }

    /**
     * Counts the number of cars owned by the specified owner ID.
     *
     * @param ownerId The unique identifier of the owner whose cars are to be counted.
     * @return The count of cars owned by the specified owner ID.
     */
    public int countCarsByOwnerId(Long ownerId) {
        return carsRepository.countCarsByOwnerId(ownerId);
    }

    /**
     * Retrieves a page of cars owned by the specified owner ID.
     *
     * @param ownerId The unique identifier of the owner whose cars are to be retrieved.
     * @param page The page number (0-based) of the results to retrieve.
     * @param size The number of cars per page.
     * @return A list of cars belonging to the specified owner ID for the requested page.
     */
    public List<Car> getPageOfCarsByOwnerId(Long ownerId, int page, int size) {
        Pageable requestedPage = PageRequest.of(page, size);

        return carsRepository.findAllByOwnerId(ownerId, requestedPage).getContent();
    }

    /**
     * Removes a car from the database.
     * @param carId The unique identifier of the car to remove.
     */
    public void deleteCar(Long carId) {
        this.carsRepository.deleteById(carId);
    }

    public List<Car> getPage(Integer pageNumber, Integer pageSize) {
        Pageable pageable = PageRequest.of(pageNumber, pageSize);

        return this.carsRepository.findAll(pageable)
            .stream()
            .collect(Collectors.toList());
    }

    /**
     * Retrieves the total number of cars in the database.
     * @return total number of cars in the database.
     */
    public Long getTotalCarCount() {
        return this.carsRepository.getTotalCarCount();
    }

    /**
     * Retrieves all cars from the database.
     * @return a list of all cars in the database.
     */
    public List<Car> getAll() {
        return this.carsRepository.findAll();
    }

    public void addCar(CarDTO carDTO) throws RepositoryException {
        Optional<User> owner = this.usersRepository.findById(carDTO.getOwnerId());

        if (owner.isEmpty())
            throw new RepositoryException("Owner not found!");

        Car carToAdd = new Car(carDTO);
        carToAdd.setOwner(owner.get());

        this.carsRepository.save(carToAdd);
    }
}
