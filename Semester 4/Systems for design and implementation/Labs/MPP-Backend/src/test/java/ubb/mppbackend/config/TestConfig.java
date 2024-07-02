package ubb.mppbackend.config;

import org.springframework.boot.test.context.TestConfiguration;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import ubb.mppbackend.config.security.JWTUtils;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

@TestConfiguration
public class TestConfig {
    @Bean
    public JWTUtils jwtUtils(UsersRepositoryJPA usersRepositoryJPA) {
        return new JWTUtils(usersRepositoryJPA);
    }
}
