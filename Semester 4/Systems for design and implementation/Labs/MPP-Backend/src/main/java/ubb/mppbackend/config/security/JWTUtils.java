package ubb.mppbackend.config.security;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.io.Decoders;
import io.jsonwebtoken.security.Keys;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.AuthenticationCredentialsNotFoundException;
import org.springframework.security.core.Authentication;
import org.springframework.stereotype.Component;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import javax.crypto.SecretKey;
import java.util.Date;
import java.util.Optional;

/**
 * Utility class for handling JWT (JSON Web Token) generation, parsing, and validation.
 */
@Component
public class JWTUtils {
    private final UsersRepositoryJPA usersRepositoryJPA;

    private final String SECRET_KEY = "2cbd5a209d9cf159fd51d1932a188ef4c3ef5c38822f439d7d2bce64a440fc4d";

    /**
     * Constructor for JWTUtils.
     *
     * @param usersRepositoryJPA UsersRepositoryJPA instance for accessing user data.
     */
    @Autowired
    public JWTUtils(UsersRepositoryJPA usersRepositoryJPA) {
        this.usersRepositoryJPA = usersRepositoryJPA;
    }

    /**
     * Generates a JWT token based on the provided authentication information.
     *
     * @param authentication Authentication object containing user details.
     * @return String representing the generated JWT token.
     */
    public String generateToken(Authentication authentication) {
        String email = authentication.getName();
        Optional<User> requiredUser = this.usersRepositoryJPA.findByEmail(email);

        if (requiredUser.isEmpty()) return null;

        return Jwts.builder()
            .claim("userID", requiredUser.get().getId().toString())
            .issuedAt(new Date())
            .signWith( this.getSigningKey())
            .compact();
    }

    /**
     * Retrieves the user ID from a given JWT token.
     *
     * @param token JWT token from which to extract the user ID.
     * @return String representing the user ID extracted from the token.
     */
    public String getIdFromJWT(String token) {
        Claims jwtBody = Jwts.parser()
            .verifyWith(this.getSigningKey())
            .build()
            .parseSignedClaims(token)
            .getPayload();

        return (String) jwtBody.get("userID");
    }

    public String getUserIdFromBearerToken(String bearerToken) {
        String jwtToken = bearerToken.substring(7);
        return this.getIdFromJWT(jwtToken);
    }

    /**
     * Validates the provided JWT token.
     *
     * @param token JWT token to be validated.
     * @return boolean indicating whether the token is valid (true) or not (false).
     * @throws AuthenticationCredentialsNotFoundException if the token validation fails (e.g., expired or incorrect token).
     */
    public boolean validateToken(String token) {
        try {
            Jwts.parser().verifyWith(this.getSigningKey()).build().parseSignedClaims(token);
            return true;
        }

        catch (Exception e) {
            throw new AuthenticationCredentialsNotFoundException("JWT was expired  or incorrect!");
        }
    }

    /**
     * Retrieves the signing key used for JWT token generation and validation.
     *
     * @return SecretKey used for signing JWT tokens.
     */
    private SecretKey getSigningKey() {
        byte[] keyBytes = Decoders.BASE64.decode(this.SECRET_KEY);

        return Keys.hmacShaKeyFor(keyBytes);
    }
}
