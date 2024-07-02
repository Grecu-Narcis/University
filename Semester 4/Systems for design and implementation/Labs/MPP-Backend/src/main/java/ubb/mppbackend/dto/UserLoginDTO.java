package ubb.mppbackend.dto;

import lombok.Data;

/**
 * Data Transfer Object (DTO) representing user login credentials.
 * This class encapsulates the email and password for user authentication.
 */
@Data
public class UserLoginDTO {
    private String email;
    private String password;
}
