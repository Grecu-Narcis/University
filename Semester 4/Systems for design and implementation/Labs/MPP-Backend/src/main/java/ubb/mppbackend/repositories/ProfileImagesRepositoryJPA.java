package ubb.mppbackend.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import ubb.mppbackend.models.user.ProfileImage;

import java.util.Optional;

/**
 * Repository interface for accessing ProfileImage entities using JPA.
 */
public interface ProfileImagesRepositoryJPA extends JpaRepository<ProfileImage, Long> {
    /**
     * Retrieves a profile image associated with a specific user ID, if it exists.
     *
     * @param userId  The ID of the user whose profile image is to be retrieved.
     * @return        An Optional containing the profile image associated with the specified user ID,
     *                or an empty Optional if no profile image is found for the user.
     */
    Optional<ProfileImage> findByUserId(Long userId);
}
