package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import ubb.mppbackend.business.ImagesService;
import ubb.mppbackend.config.security.JWTUtils;

import java.nio.file.FileAlreadyExistsException;
import java.util.Base64;

/**
 * Controller class responsible for handling RESTful endpoints related to user images.
 */
@RestController
@RequestMapping("/api/images")
@CrossOrigin(origins = "*")
public class ImagesController {
    private final ImagesService profileImagesService;
    private final JWTUtils jwtUtils;

    /**
     * Constructor for initializing the ImagesController with required dependencies.
     *
     * @param profileImagesService The service responsible for managing user images.
     * @param jwtUtils             Utility class for parsing and validating JWT tokens.
     */
    @Autowired
    public ImagesController(ImagesService profileImagesService, JWTUtils jwtUtils) {
        this.profileImagesService = profileImagesService;
        this.jwtUtils = jwtUtils;
    }

    /**
     * Retrieves a user's image by their userId.
     *
     * @param userId       The ID of the user whose image is being requested.
     * @return             ResponseEntity containing the requested image as a Base64 encoded string.
     */
    @GetMapping("/getImage/{userId}")
    public ResponseEntity<String> getImageByUserId(@PathVariable Long userId) {
        try {
            byte[] requiredImage = this.profileImagesService.getImage(userId);

            String encodedImage = Base64.getEncoder().encodeToString(requiredImage);
            return ResponseEntity.ok().body(encodedImage);
        } catch (Exception e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    /**
     * Saves a user's image to the storage system.
     *
     * @param imageToSave  The image file to be saved.
     * @param userId       The ID of the user to whom the image belongs.
     * @param bearerToken  The JWT bearer token used for authorization.
     * @return             ResponseEntity indicating the success or failure of the operation.
     */
    @PostMapping("/saveImage")
    public ResponseEntity<String> saveImage(@RequestParam("image") MultipartFile imageToSave,
                                            @RequestParam("userId") Long userId,
                                            @RequestHeader("Authorization") String bearerToken) {
        String authorizedUserId = jwtUtils.getUserIdFromBearerToken(bearerToken);

        if (!authorizedUserId.equals(userId.toString()))
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();

        try {
            this.profileImagesService.saveImageToStorage(userId, imageToSave);
            return ResponseEntity.ok().body("File saved successfully!");
        }
        catch (Exception e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }
}
