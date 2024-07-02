package ubb.mppbackend.repositories;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import ubb.mppbackend.models.car.Car;

import java.util.List;

/**
 * Repository interface for accessing Car entities using JPA.
 */
public interface CarsRepositoryJPA extends JpaRepository<Car, Long> {
    /**
     * Retrieves a list of cars owned by a specific owner.
     *
     * @param ownerId  The ID of the owner whose cars are to be retrieved.
     * @return         A list of cars owned by the specified owner.
     */
    List<Car> findAllByOwnerId(Long ownerId);

    /**
     * Retrieves a page of cars owned by a specific owner with pagination support.
     *
     * @param ownerId   The ID of the owner whose cars are to be retrieved.
     * @param pageable  The pagination information (e.g., page number, page size, sorting).
     * @return          A page containing cars owned by the specified owner.
     */
    Page<Car> findAllByOwnerId(Long ownerId, Pageable pageable);

    /**
     * Counts the number of cars owned by a specific owner.
     *
     * @param ownerId  The ID of the owner whose cars are to be counted.
     * @return         The total count of cars owned by the specified owner.
     */
    @Query("SELECT count(*) FROM cars c where c.owner.id = ?1")
    int countCarsByOwnerId(Long ownerId);

    /**
     * Retrieves the total number of cars in the database.
     * @return total number of cars in the database.
     */
    @Query("SELECT count(c) FROM cars c")
    Long getTotalCarCount();
}
