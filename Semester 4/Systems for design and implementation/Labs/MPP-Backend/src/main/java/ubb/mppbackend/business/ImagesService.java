package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;
import ubb.mppbackend.models.user.ProfileImage;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.ProfileImagesRepositoryJPA;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.Optional;
import java.util.UUID;

/**
 * Service class that manages operations related to user profile images.
 * This class interacts with a ProfileImagesRepositoryJPA and UsersRepositoryJPA
 * to store, retrieve, and delete profile images associated with users.
 */
@Service
public class ImagesService {
    ProfileImagesRepositoryJPA profileImagesRepository;
    UsersRepositoryJPA usersRepository;
    private final String uploadDirectory = "./src/main/resources/profile-images";

    /**
     * Constructs a new ImagesService instance with the specified dependencies.
     *
     * @param profileImagesRepository The repository for managing profile image data.
     * @param usersRepository         The repository for accessing user data.
     */
    @Autowired
    public ImagesService(ProfileImagesRepositoryJPA profileImagesRepository, UsersRepositoryJPA usersRepository) {
        this.profileImagesRepository = profileImagesRepository;
        this.usersRepository = usersRepository;
    }

    /**
     * Saves a profile image to the storage directory and associates it with the specified user ID.
     *
     * @param userId      The ID of the user to associate the image with.
     * @param imageToSave The image file to save.
     * @throws Exception If there is an error saving the image or associating it with the user.
     */
    public void saveImageToStorage(Long userId, MultipartFile imageToSave) throws Exception {
        Optional<User> requiredUser = usersRepository.findById(userId);

        if (requiredUser.isEmpty()) {
            throw new Exception("User not found");
        }

        this.removeUserProfileImage(requiredUser.get().getId());

        String imageUrl = UUID.randomUUID() + imageToSave.getOriginalFilename();
        Path uploadPath = Path.of(uploadDirectory, imageUrl);
        System.out.println(uploadPath);
        Files.copy(imageToSave.getInputStream(), uploadPath, StandardCopyOption.REPLACE_EXISTING);

        ProfileImage profileImage = new ProfileImage(imageUrl, requiredUser.get());
        profileImagesRepository.save(profileImage);
    }

    /**
     * Removes the profile image associated with the specified user ID from the storage directory.
     *
     * @param userId The ID of the user whose profile image is to be removed.
     * @throws IOException If there is an error deleting the image file.
     */
    public void removeUserProfileImage(Long userId) throws IOException {
        Optional<ProfileImage> requiredImage = profileImagesRepository.findByUserId(userId);
        if (requiredImage.isEmpty())
            return;

        requiredImage.ifPresent(profileImage -> this.profileImagesRepository.delete(profileImage));
        String imageToRemovePath = uploadDirectory + "/" + requiredImage.get().getImageUrl();

        Path pathToRemove = Path.of(imageToRemovePath);

        if (!Files.exists(pathToRemove)) {
            System.out.println("not exists");
            return;
        }

        Files.delete(pathToRemove);
    }

    /**
     * Retrieves the profile image data (as byte array) associated with the specified user ID.
     * If no profile image is found for the user, a default image (dog.jpg) is returned.
     *
     * @param userId The ID of the user whose profile image data is to be retrieved.
     * @return The byte array representing the user's profile image.
     * @throws IOException If there is an error reading the image file.
     */
    public byte[] getImage(Long userId) throws IOException {
        Optional<ProfileImage> profileImage = profileImagesRepository.findByUserId(userId);

        if (profileImage.isEmpty()) {
            Path filePath = Path.of(this.uploadDirectory, "dog.jpg");
            return Files.readAllBytes(filePath);
        }

        try {
            Path filePath = Path.of(this.uploadDirectory, profileImage.get().getImageUrl());
            return Files.readAllBytes(filePath);
        }
        catch (IOException e) {
            Path filePath = Path.of(this.uploadDirectory, "dog.jpg");
            return Files.readAllBytes(filePath);
        }
    }
}
