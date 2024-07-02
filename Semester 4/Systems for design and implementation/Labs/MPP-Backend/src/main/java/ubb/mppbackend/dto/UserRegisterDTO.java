package ubb.mppbackend.dto;

import lombok.*;

/**
 * Data Transfer Object (DTO) representing user registration information.
 */
@Data
public class UserRegisterDTO {
    private String firstName;
    private String lastName;
    private String email;
    private String password;
    private String userRole;
}
