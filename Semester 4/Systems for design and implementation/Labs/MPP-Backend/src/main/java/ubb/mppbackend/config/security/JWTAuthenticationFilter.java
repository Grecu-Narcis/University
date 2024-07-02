package ubb.mppbackend.config.security;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.lang.NonNull;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.filter.OncePerRequestFilter;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.io.IOException;
import java.util.Optional;

/**
 * This filter intercepts incoming requests to validate and process JWT (JSON Web Token) authentication.
 */
@Component
public class JWTAuthenticationFilter extends OncePerRequestFilter {
    @Autowired
    private JWTUtils jwtUtils;

    @Autowired
    private CustomUserDetailsService customUserDetailsService;

    @Autowired
    private UsersRepositoryJPA usersRepositoryJPA;

    /**
     * Filters incoming requests to validate and process JWT authentication.
     *
     * @param request     The HTTP request
     * @param response    The HTTP response
     * @param filterChain The filter chain for processing the request
     * @throws ServletException If an error occurs within the servlet or filter
     * @throws IOException      If an I/O error occurs during the filtering process
     */
    @Override
    protected void doFilterInternal(@NonNull HttpServletRequest request,
                                    @NonNull HttpServletResponse response,
                                    @NonNull FilterChain filterChain) throws IOException, ServletException {
        // Extract JWT token from the request
        String token = getJWTFromRequest(request);

        // If token is missing or invalid, proceed to the next filter in the chain
        if (!StringUtils.hasText(token) || !jwtUtils.validateToken(token)) {
            filterChain.doFilter(request, response);
            return;
        }

        // Retrieve user ID from the validated JWT token and fetch user details from the repository based on it
        Long userId = Long.parseLong(jwtUtils.getIdFromJWT(token));
        Optional<User> requiredUser = this.usersRepositoryJPA.findById(userId);

        // If user not found, proceed to the next filter
        if (requiredUser.isEmpty()) {
            filterChain.doFilter(request, response);
            return;
        }

        UserDetails userDetails = customUserDetailsService.loadUserByUsername(requiredUser.get().getEmail());
        UsernamePasswordAuthenticationToken authenticationToken = new UsernamePasswordAuthenticationToken(
            userDetails,
            null,
            userDetails.getAuthorities()
        );

        authenticationToken.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));
        SecurityContextHolder.getContext().setAuthentication(authenticationToken);

        filterChain.doFilter(request, response);
    }

    /**
     * Extracts the JWT token from the request header.
     *
     * @param request The HTTP request
     * @return The JWT token (without the 'Bearer ' prefix), or null if not found
     */
    private String getJWTFromRequest(HttpServletRequest request) {
        String bearerToken = request.getHeader("Authorization");

        if (StringUtils.hasText(bearerToken) && bearerToken.startsWith("Bearer "))
            return bearerToken.substring(7);

        return null;
    }
}
