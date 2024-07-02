package ubb.mppbackend.dto;

import lombok.*;
import ubb.mppbackend.models.user.User;

/**
 * Data Transfer Object (DTO) representing user data.
 * This class is used for transferring user information between layers of the application.
 */
@Getter
@Setter
@AllArgsConstructor
@ToString
@NoArgsConstructor
public class UserDTO {
    private Long id;
    private String firstName;
    private String lastName;
    private String email;
    private String userRole;
    /**
     * Constructs a UserDTO object based on the provided User object.
     *
     * @param userToConvert The User object from which to construct the UserDTO.
     */
    public UserDTO(User userToConvert) {
        this.id = userToConvert.getId();
        this.firstName = userToConvert.getFirstName();
        this.lastName = userToConvert.getLastName();
        this.email = userToConvert.getEmail();
        this.userRole = userToConvert.getRoles().stream().findFirst().get().getName();
    }
}
