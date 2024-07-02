package ubb.mppbackend.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import ubb.mppbackend.models.role.Role;

import java.util.Optional;

/**
 * This repository interface provides access to Role entities stored in the database.
 * Role entities represent user roles within the application.
 */
public interface RoleRepositoryJPA extends JpaRepository<Role, Long> {
    /**
     * Retrieves a role by its name from the repository, if present.
     *
     * @param name The name of the role to search for.
     * @return An Optional containing the role with the specified name, if found; otherwise, an empty Optional.
     */
    Optional<Role> findByName(String name);
}
