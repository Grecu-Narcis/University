package ubb.mppbackend.config.security;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.web.AuthenticationEntryPoint;
import org.springframework.stereotype.Component;

import java.io.IOException;

/**
 * This class implements the AuthenticationEntryPoint interface to handle
 * authentication failures during a JWT-based authentication process.
 * It sends an HTTP error response with status code 401 (Unauthorized) when
 * authentication fails due to an AuthenticationException.
 */
@Component
public class JWTAuthenticationEntryPoint implements AuthenticationEntryPoint {
    /**
     * Invoked when a user tries to access a secured REST resource without providing
     * valid authentication credentials (JWT token), resulting in an authentication failure.
     * This method sends an HTTP response with status code 401 (Unauthorized) and includes
     * the specific error message from the AuthenticationException.
     *
     * @param request       the HTTP request made by the client
     * @param response      the HTTP response to be sent back to the client
     * @param authException the AuthenticationException that caused the authentication failure
     * @throws IOException      in case of an I/O error while sending the response
     */
    @Override
    public void commence(HttpServletRequest request, HttpServletResponse response, AuthenticationException authException) throws IOException {
        response.sendError(HttpServletResponse.SC_UNAUTHORIZED, authException.getMessage());
    }
}
