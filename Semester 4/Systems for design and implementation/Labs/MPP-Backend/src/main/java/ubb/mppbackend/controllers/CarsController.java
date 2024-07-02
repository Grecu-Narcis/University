package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.Authentication;
import org.springframework.web.bind.annotation.*;
import ubb.mppbackend.business.CarsService;
import ubb.mppbackend.business.UsersService;
import ubb.mppbackend.config.security.JWTUtils;
import ubb.mppbackend.dto.CarDTO;
import ubb.mppbackend.models.car.Car;
import ubb.mppbackend.models.user.User;

import java.util.List;

/**
 * RestController class responsible for handling API endpoints related to cars.
 * Endpoints are mapped under "/api/cars" with cross-origin support enabled for all origins.
 */
@RestController
@RequestMapping("/api/cars")
@CrossOrigin(origins = "*")
public class CarsController {
    private final CarsService carsService;
    private final JWTUtils jwtUtils;

    /**
     * Constructor for initializing the CarsController with necessary dependencies.
     *
     * @param carsService The service responsible for handling car-related operations.
     * @param jwtUtils    Utility class for processing JSON Web Tokens (JWTs).
     */
    @Autowired
    public CarsController(CarsService carsService, JWTUtils jwtUtils) {
        this.carsService = carsService;
        this.jwtUtils = jwtUtils;
    }

    /**
     * Retrieves all cars owned by a specified owner ID.
     *
     * @param ownerId     The ID of the owner whose cars are to be retrieved.
     * @return ResponseEntity containing a list of cars belonging to the specified owner if authorized,
     *         otherwise returns HTTP status UNAUTHORIZED.
     */
    @GetMapping("/getAllByOwnerId/{ownerId}")
    public ResponseEntity<List<Car>> getCarsByOwnerId(@PathVariable String ownerId) {

        List<Car> cars = this.carsService.getAllCarsByOwnerId(Long.parseLong(ownerId));
        System.out.println(cars);
        return ResponseEntity.ok().body(cars);
    }

    /**
     * Retrieves a paginated list of cars owned by a specified owner ID.
     *
     * @param ownerId     The ID of the owner whose cars are to be retrieved.
     * @param page        The page number for pagination (starting from 0).
     * @param pageSize    The maximum number of cars per page.
     * @return ResponseEntity containing a paginated list of cars if authorized,
     *         otherwise returns HTTP status UNAUTHORIZED.
     */
    @GetMapping("/getPageByOwnerId")
    public ResponseEntity<List<Car>> getPageByOwnerId(@RequestParam String ownerId,
                                                      @RequestParam String page,
                                                      @RequestParam String pageSize) {
        List<Car> cars = this.carsService.getPageOfCarsByOwnerId(Long.parseLong(ownerId), Integer.parseInt(page), Integer.parseInt(pageSize));
        return ResponseEntity.ok().body(cars);
    }

    /**
     * Retrieves a paginated list of cars.
     * @param pageNumber The page number (0-based) of the results to retrieve.
     * @param pageSize The number of cars per page.
     * @return ResponseEntity containing a paginated list of cars if authorized,
     *        otherwise returns HTTP status BAD_REQUEST.
     */
    @PreAuthorize("hasAuthority('ADMIN')")
    @GetMapping("/getPage")
    public ResponseEntity<List<Car>> getPage(@RequestParam(name = "page") Integer pageNumber,
                                             @RequestParam(name = "size") Integer pageSize) {
        try {
            System.out.println("hello");
            return ResponseEntity.ok().body(this.carsService.getPage(pageNumber, pageSize));
        }
        catch (Exception e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
        }
    }

    /**
     * Retrieves all cars in the database.
     * @return ResponseEntity containing a list of all cars if authorized,
     *       otherwise returns HTTP status UNAUTHORIZED or BAD_REQUEST.
     */
    @PreAuthorize("hasAuthority('ADMIN')")
    @GetMapping("/getAll")
    public ResponseEntity<List<Car>> getAll() {
        try {
            return ResponseEntity.ok().body(this.carsService.getAll());
        }
        catch (Exception e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
        }
    }

    /**
     * Retrieves the total number of cars in the database.
     * @return ResponseEntity containing the total number of cars if authorized,
     *       otherwise returns HTTP status UNAUTHORIZED or INTERNAL_SERVER_ERROR.
     */
    @PreAuthorize("hasAuthority('ADMIN')")
    @GetMapping("/getTotalCarCount")
    public ResponseEntity<Long> getTotalCarCount() {
        try {
            return ResponseEntity.ok().body(this.carsService.getTotalCarCount());
        }
        catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    /**
     * Retrieves a specific car by its ID.
     *
     * @param carId       The ID of the car to retrieve.
     * @return ResponseEntity containing the requested car if authorized,
     *         otherwise returns HTTP status UNAUTHORIZED or NOT_FOUND if the car does not exist.
     */
    @GetMapping("/getCar/{carId}")
    public ResponseEntity<Car> getCarById(@PathVariable String carId) {
        try {
            Car requiredCar = this.carsService.getCarById(Long.parseLong(carId));

            return ResponseEntity.ok().body(requiredCar);
        }

        catch (Exception e) {
            return ResponseEntity.notFound().build();
        }
    }

    /**
     * Retrieves the count of cars owned by a specified owner ID.
     *
     * @param ownerId     The ID of the owner whose cars are to be counted.
     * @return ResponseEntity containing the count of cars if authorized,
     *         otherwise returns HTTP status UNAUTHORIZED.
     */
    @GetMapping("/getCarsCount/{ownerId}")
    public ResponseEntity<Integer> getCarsCountByOwnerId(@PathVariable String ownerId) {
        int count = this.carsService.countCarsByOwnerId(Long.parseLong(ownerId));
        return ResponseEntity.ok().body(count);
    }

    @PreAuthorize("hasAuthority('MANAGER')")
    @PostMapping("/addCar")
    public ResponseEntity<?> addCar(@RequestBody CarDTO carDTO) {
        try {
            this.carsService.addCar(carDTO);
            return ResponseEntity.ok().body("Car added successfully!");
        }
        catch (Exception e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    /**
     * Updates information of a specified car.
     *
     * @param carToAdd     The car object containing updated information.
     * @param bearerToken  The authorization token (Bearer token) provided in the request header.
     * @return ResponseEntity indicating the status of the update operation,
     *         with success message if authorized and completed,
     *         otherwise returns HTTP status UNAUTHORIZED or BAD_REQUEST.
     */
    @PreAuthorize("hasAuthority('ADMIN') or hasAuthority('MANAGER')")
    @PutMapping("/updateCar")
    public ResponseEntity<String> updateCar(@RequestBody Car carToAdd,
                                            @RequestHeader("Authorization") String bearerToken,
                                            Authentication authentication) {
        String authorizedUserId = jwtUtils.getUserIdFromBearerToken(bearerToken);
        try {
            User owner = this.carsService.getCarById(carToAdd.getId()).getOwner();
            if (!authorizedUserId.equals(owner.getId().toString()) &&
                !UsersService.isAdmin(authentication))
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
            carToAdd.setOwner(owner);
            this.carsService.updateCar(carToAdd);
            return ResponseEntity.ok().body("Car added successfully!");
        }

        catch (Exception e) {
            return ResponseEntity.badRequest().body("Invalid car data!");
        }
    }

    /**
     * Deletes a specified car by its ID.
     * @param carId The ID of the car to delete.
     * @param bearerToken The authorization token (Bearer token) provided in the request header.
     * @param authentication The authentication object containing user details.
     * @return ResponseEntity indicating the status of the delete operation,
     *        with success message if authorized and completed,
     *        otherwise returns HTTP status UNAUTHORIZED or BAD_REQUEST.
     */
    @PreAuthorize("hasAuthority('ADMIN') or hasAuthority('MANAGER')")
    @DeleteMapping("/deleteCar/{carId}")
    public ResponseEntity<String> deleteCar(@PathVariable String carId,
                                            @RequestHeader("Authorization") String bearerToken,
                                            Authentication authentication) {
        String authorizedUserId = jwtUtils.getUserIdFromBearerToken(bearerToken);

        try {
            Car car = this.carsService.getCarById(Long.parseLong(carId));
            User owner = car.getOwner();

            if (!authorizedUserId.equals(owner.getId().toString()) &&
                !UsersService.isAdmin(authentication))
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();

            this.carsService.deleteCar(Long.parseLong(carId));
            return ResponseEntity.ok().body("Car deleted successfully!");
        }

        catch (Exception e) {
            return ResponseEntity.badRequest().body("Invalid car ID!");
        }
    }
}
