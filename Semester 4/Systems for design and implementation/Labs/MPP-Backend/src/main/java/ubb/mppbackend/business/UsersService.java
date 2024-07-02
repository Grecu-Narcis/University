package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.scheduling.annotation.Async;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.security.core.Authentication;
import org.springframework.stereotype.Service;
import ubb.mppbackend.dto.UserDTO;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.exceptions.UserValidatorException;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.models.user.UserMockGenerator;
import ubb.mppbackend.models.user.UserValidator;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.List;
import java.util.Optional;
import java.util.concurrent.TimeUnit;

/**
 * Service class that manages operations related to users.
 * This class interacts with a UsersRepositoryJPA to perform CRUD operations on User entities.
 * It also includes methods for sending user data over WebSocket periodically.
 */
@Service
public class UsersService {
    private final UsersRepositoryJPA usersRepository;
    private final SimpMessagingTemplate messagingTemplate;

    /**
     * Constructs a new UsersService instance with the specified dependencies.
     *
     * @param usersRepository   The repository for accessing and managing user data.
     * @param messagingTemplate The template for sending messages over WebSocket.
     */
    @Autowired
    public UsersService(UsersRepositoryJPA usersRepository, SimpMessagingTemplate messagingTemplate) {
        this.usersRepository = usersRepository;
        this.messagingTemplate = messagingTemplate;

//        UserMockGenerator.generateFakeData(1000, usersRepository);
    }

    /**
     * Sends fake user data periodically over WebSocket every 5 seconds.
     * This method is executed asynchronously at a fixed rate.
     * Note: Uncomment the implementation in this method to activate the periodic data sending.
     */
    @Scheduled(fixedRate = 5, timeUnit = TimeUnit.SECONDS)
    @Async
    public void sendFakeUserDataPeriodically() {
        // Uncomment the following lines to send fake user data every 5 seconds
        // System.out.println("This runs every 5 seconds!");
        // messagingTemplate.convertAndSend("/topic/users", UserMockGenerator.generateFakeData(5, this.usersRepository));
    }

    /**
     * Retrieves a user by their unique identifier.
     *
     * @param idToSearch The ID of the user to retrieve.
     * @return The user with the specified ID.
     * @throws RepositoryException If no user is found with the specified ID.
     */
    public User getById(Long idToSearch) throws RepositoryException {
        Optional<User> foundUser = this.usersRepository.findById(idToSearch);

        if (foundUser.isEmpty())
            throw new RepositoryException("User not found!");

        return foundUser.get();
    }

    /**
     * Adds a new user to the repository.
     *
     * @param userToAdd The user to add.
     * @throws UserValidatorException If the user data is invalid.
     */
    public void addUser(User userToAdd) throws UserValidatorException {
        UserValidator.validate(userToAdd);

        this.usersRepository.save(userToAdd);
    }

    /**
     * Updates an existing user in the repository.
     *
     * @param userDTO The updated user information.
     * @throws UserValidatorException If the updated user data is invalid.
     * @throws RepositoryException    If the user to update is not found in the repository.
     */
    public void updateUser(UserDTO userDTO) throws UserValidatorException, RepositoryException {
        Optional<User> userToUpdate = this.usersRepository.findById(userDTO.getId());
        if (userToUpdate.isEmpty())
            throw new RepositoryException("User not found!");

        User newUser = userToUpdate.get();
        newUser.setFirstName(userDTO.getFirstName());
        newUser.setLastName(userDTO.getLastName());
        newUser.setEmail(userDTO.getEmail());

        UserValidator.validate(newUser);

        this.usersRepository.save(newUser);
    }

    /**
     * Deletes a user from the repository by their ID.
     *
     * @param idToRemove The ID of the user to delete.
     */
    public void deleteUser(Long idToRemove) {
        this.usersRepository.deleteById(idToRemove);
    }

    /**
     * Retrieves a page of users sorted by age.
     *
     * @param requiredPage The page number (0-based) of the results to retrieve.
     * @param isAscending  true to sort in ascending order, false to sort in descending order by age.
     * @param pageSize     The number of users per page.
     * @return A list of users for the specified page, sorted by age.
     */
    public List<User> getPage(int requiredPage, boolean isAscending, int pageSize) {
        Sort sort = Sort.by(isAscending ? Sort.Direction.ASC : Sort.Direction.DESC, "id");
        Pageable requestedPage = PageRequest.of(requiredPage, pageSize, sort);

        return this.usersRepository.findAll(requestedPage).getContent();
    }

    /**
     * Retrieves all users from the repository.
     *
     * @return A list of all users in the repository.
     */
    public List<User> getAll() {
        return this.usersRepository.findAll();
    }

    /**
     * Counts the total number of users in the repository.
     *
     * @return The total count of users.
     */
    public int countUsers() {
        return this.usersRepository.countUsers();
    }

    /**
     * Adds a list of users to the repository.
     *
     * @param usersToAdd The list of users to add.
     * @throws UserValidatorException If any user data in the list is invalid.
     */
    public void addUsers(List<User> usersToAdd) throws UserValidatorException {
        for (User userToAdd : usersToAdd) {
            UserValidator.validate(userToAdd);
            this.usersRepository.save(userToAdd);
        }
    }

    public boolean existsByEmail(String email) {
        return this.usersRepository.existsByEmail(email);
    }

    public Optional<User> findByEmail(String email) {
        return this.usersRepository.findByEmail(email);
    }

    /**
     * Checks if the provided authentication object is an admin.
     * @param authentication The authentication object to check.
     * @return True if the authentication object is an admin, false otherwise.
     */
    public static boolean isAdmin(Authentication authentication) {
        if (authentication == null) return false;

        return authentication.getAuthorities()
            .stream()
            .anyMatch(authority -> authority.getAuthority().contains("ADMIN"));
    }
}
