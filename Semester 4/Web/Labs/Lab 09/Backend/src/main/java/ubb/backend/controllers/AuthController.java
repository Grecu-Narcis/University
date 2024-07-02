package ubb.java.controllers;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ubb.backend.dtos.LoginRequest;
import ubb.backend.dtos.LoginResponse;
import ubb.backend.models.DBManager;
import ubb.backend.models.User;


@RestController
@RequestMapping("/api/auth")
@CrossOrigin(origins = "*")
public class AuthController {
    @PostMapping("/login")
    public ResponseEntity<LoginResponse> login(@RequestBody LoginRequest loginRequest) {
        String username = loginRequest.username;
        String password = loginRequest.password;

        User requiredUser = DBManager.getUserByUsername(username);

        if (requiredUser == null)
            return ResponseEntity.status(HttpStatus.NOT_FOUND).build();

        if (!requiredUser.password.equals(password))
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();

        return ResponseEntity.ok().body(new LoginResponse(requiredUser.userId));
    }
}
