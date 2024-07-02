package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;
import ubb.mppbackend.business.EmailService;
import ubb.mppbackend.business.RoleService;
import ubb.mppbackend.business.UsersService;
import ubb.mppbackend.config.security.JWTUtils;
import ubb.mppbackend.dto.AuthResponseDTO;
import ubb.mppbackend.dto.UserLoginDTO;
import ubb.mppbackend.dto.UserRegisterDTO;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.exceptions.UserValidatorException;
import ubb.mppbackend.models.role.Role;
import ubb.mppbackend.models.user.User;

import java.util.Optional;
import java.util.Set;

/**
 * Controller responsible for handling user authentication operations via API endpoints.
 * Endpoints are mapped under "/api/auth" with cross-origin support enabled for all origins.
 */
@RestController
@RequestMapping("/api/auth")
@CrossOrigin(origins = "*")
public class AuthenticationController {
    private final AuthenticationManager authenticationManager;
    private final UsersService usersService;
    private final RoleService roleService;
    private final PasswordEncoder passwordEncoder;
    private final JWTUtils jwtUtils;
    private final EmailService emailService;

    /**
     * Constructs a new AuthenticationController with required dependencies.
     *
     * @param authenticationManager The authentication manager used to authenticate users.
     * @param passwordEncoder       The password encoder for securely encoding passwords.
     * @param usersService          The service for managing user data.
     * @param roleService           The service for managing user roles.
     * @param jwtUtils              The utility class for handling JWT (JSON Web Token) operations.
     * @param emailService          The service for sending emails to users.
     */
    @Autowired
    public AuthenticationController(AuthenticationManager authenticationManager, PasswordEncoder passwordEncoder,
                                    UsersService usersService, RoleService roleService,
                                    JWTUtils jwtUtils, EmailService emailService) {
        this.authenticationManager = authenticationManager;
        this.usersService = usersService;
        this.roleService = roleService;
        this.passwordEncoder = passwordEncoder;
        this.jwtUtils = jwtUtils;
        this.emailService = emailService;
    }

    /**
     * Endpoint for user registration.
     *
     * @param registerRequest The user registration request containing user details.
     * @return ResponseEntity indicating the result of the registration process.
     * @throws RepositoryException If an error occurs during data repository operations.
     */
    @PostMapping("/register")
    public ResponseEntity<String> register(@RequestBody UserRegisterDTO registerRequest) throws RepositoryException
    {
        try {
            if (this.usersService.existsByEmail(registerRequest.getEmail()))
                return ResponseEntity.badRequest().body("There already exists an account with this email!");

            User userToRegister = new User(registerRequest.getFirstName(), registerRequest.getLastName(),
                registerRequest.getEmail(), this.passwordEncoder.encode(registerRequest.getPassword()));

            Optional<Role> userRole = this.roleService.findByName(registerRequest.getUserRole());
            if (userRole.isEmpty())
                throw new RepositoryException("Role not found!");

            userToRegister.setRoles(Set.of(userRole.get()));
            this.usersService.addUser(userToRegister);

            this.emailService.sendEmail(registerRequest.getEmail(), "Account created successfully",
                "Welcome to TravelWheels!\nYour account has been created successfully!");

            return ResponseEntity.ok().body("User registered successfully!");
        }
        catch (UserValidatorException e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(e.getMessage());
        }
    }

    /**
     * Endpoint for user login.
     *
     * @param loginRequest The user login request containing login credentials.
     * @return ResponseEntity containing an authentication token upon successful login.
     */
    @PostMapping("/login")
    public ResponseEntity<AuthResponseDTO> login(@RequestBody UserLoginDTO loginRequest) {
        try {
            Authentication authentication = this.authenticationManager.authenticate(
                new UsernamePasswordAuthenticationToken(loginRequest.getEmail(), loginRequest.getPassword())
            );

            SecurityContextHolder.getContext().setAuthentication(authentication);
            String token = jwtUtils.generateToken(authentication);

            Optional<User> loggedUser = this.usersService.findByEmail(loginRequest.getEmail());

            //noinspection OptionalIsPresent
            if (loggedUser.isEmpty())
                return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();

            return ResponseEntity.ok().body(
                new AuthResponseDTO(token, loggedUser.get().getId(),
                    loggedUser.get().getRoles().stream().findFirst().get().getName()
                )
            );
        }
        catch (BadCredentialsException badCredentialsException) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(
                new AuthResponseDTO("Invalid username or password!", -1L, ""));
        }

        catch (AuthenticationException authenticationException) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(
                new AuthResponseDTO("Authentication failed!", -1L, ""));
        }
    }
}
