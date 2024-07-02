package ubb.mppbackend.repositories;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import ubb.mppbackend.models.user.User;

import java.util.List;
import java.util.Optional;

/**
 * Repository interface for accessing User entities using JPA.
 */
public interface UsersRepositoryJPA extends JpaRepository<User, Long> {
    /**
     * Counts the total number of users in the repository.
     *
     * @return  The total count of users stored in the repository.
     */
    @Query("SELECT count(*) FROM users")
    int countUsers();

    /**
     * Retrieves a user by their email address from the repository, if present.
     *
     * @param email The email address of the user to search for.
     * @return An Optional containing the user with the specified email, if found; otherwise, an empty Optional.
     */
    Optional<User> findByEmail(String email);

    /**
     * Checks if a user with the specified email address exists in the repository.
     *
     * @param email The email address to check for existence.
     * @return true if a user with the specified email exists in the repository; false otherwise.
     */
    Boolean existsByEmail(String email);

    /**
     * Retrieves a user by their email address and role name from the repository, if present.
     * @param roleName The name of the role to search for.
     * @param userEmail The email address of the user to search for.
     * @return An Optional containing the user with the specified email and role, if found; otherwise, an empty Optional.
     */
    @Query("SELECT u FROM users u JOIN u.roles r WHERE r.name = :roleName AND u.email = :userEmail")
    Optional<User> findByRoleAndEmail(String roleName, String userEmail);

    /**
     * Retrieves all users with the specified role from the repository.
     * @param roleName The name of the role to search for.
     * @return A list of users with the specified role.
     */
    @Query("SELECT u FROM users u JOIN u.roles r WHERE r.name = :roleName")
    Page<User> findAllByRole(String roleName, Pageable pageable);

    /**
     * Retrieves all users with the specified role from the repository.
     * @param roleName The name of the role to search for.
     * @return A list of users with the specified role.
     */
    @Query(value = "SELECT u FROM users u JOIN u.roles r WHERE r.name = :roleName")
    List<User> findAllByRole(String roleName);

    /**
     * Retrieves all users with the specified role and name from the repository.
     * @param roleName The name of the role to search for.
     * @param userName The name of the user to search for.
     * @param pageable The pagination information for the query.
     * @return A list of users with the specified role and name.
     */
    @Query(value = "SELECT u FROM users u JOIN u.roles r WHERE r.name = :roleName AND " +
        "LOWER(CONCAT(u.firstName, ' ', u.lastName)) LIKE CONCAT('%', LOWER(:userName), '%')")
    Page<User> findAllByRoleAndUserName(String roleName, String userName, Pageable pageable);

    /**
     * Counts the total number of users with the specified role in the repository.
     * @param roleName The name of the role to search for.
     * @return The total count of users with the specified role stored in the repository.
     */
    @Query("SELECT count(*) FROM users u JOIN u.roles r WHERE r.name = :roleName")
    Long countAllByRole(String roleName);

    @Query(value = "SELECT count(*) FROM users u JOIN u.roles r WHERE r.name = :roleName AND " +
        "LOWER(CONCAT(u.firstName, ' ', u.lastName)) LIKE CONCAT('%', LOWER(:userName), '%')")
    Long countAllByRoleAndUserName(String roleName, String userName);
}