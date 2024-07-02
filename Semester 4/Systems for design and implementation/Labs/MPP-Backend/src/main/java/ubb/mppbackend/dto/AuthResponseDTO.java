package ubb.mppbackend.dto;

import lombok.Data;

/**
 * Data Transfer Object (DTO) representing the authentication response.
 * This class encapsulates the details of an authentication token response.
 */
@Data
public class AuthResponseDTO {
    /**
     * The access token issued upon successful authentication.
     */
    private String accessToken;

    /**
     * The user ID associated with the access token.
     */
    private Long userId;

    /**
     * The type of token. By default, this is set to "Bearer ".
     */
    private String tokenType = "Bearer ";

    /**
     * The role of the user associated with the access token.
     */
    private String userRole;

    /**
     * Constructs a new AuthResponseDTO with the specified access token.
     *
     * @param accessToken The access token to be included in the response.
     */
    public AuthResponseDTO(String accessToken, Long userId, String userRole) {
        this.accessToken = accessToken;
        this.userId = userId;
        this.userRole = userRole;
    }
}
