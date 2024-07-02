package ubb.mppbackend.test_controllers;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.context.annotation.Import;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.test.context.support.WithMockUser;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;
import ubb.mppbackend.business.CarsService;
import ubb.mppbackend.config.TestConfig;
import ubb.mppbackend.config.security.*;
import ubb.mppbackend.controllers.CarsController;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.models.car.Car;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.List;
import java.util.Optional;

import static org.hamcrest.Matchers.is;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@WebMvcTest(CarsController.class)
@Import({TestConfig.class, SecurityConfig.class, JWTAuthenticationEntryPoint.class, CustomAccessDeniedHandler.class})
public class CarsControllerTests {
    @Autowired private MockMvc mockMvc;
    @Autowired private ObjectMapper objectMapper;
    @MockBean private CarsService carsService;
    @MockBean private UsersRepositoryJPA usersRepositoryJPA;
    @MockBean private CustomUserDetailsService customUserDetailsService;
    @Autowired private JWTUtils jwtUtils;
    private String jwtToken;

    @BeforeEach
    public void setUp() {
        User mockUser = new User("narcis", "grecu", "narcis@email.com", "secret");
        mockUser.setId((long) 1);

        Mockito.when(this.usersRepositoryJPA.findById((long) 1)).thenReturn(Optional.of(mockUser));
        Mockito.when(this.usersRepositoryJPA.findByEmail("narcis@email.com")).thenReturn(Optional.of(mockUser));

        this.jwtToken = jwtUtils.generateToken(new UsernamePasswordAuthenticationToken(
            "narcis@email.com",
            "secret"
        ));

        UserDetails mockUserDetails = org.springframework.security.core.userdetails.User
            .withUsername("narcis@email.com")
            .password("secret")
            .roles("MANAGER")
            .authorities("MANAGER")
            .build();

        Mockito.when(customUserDetailsService.loadUserByUsername("narcis@email.com")).thenReturn(mockUserDetails);
    }

    @Test
    @WithMockUser
    public void testGetCarSuccess() throws Exception {
        User testUser = new User("narcis", "test", "test", "test");
        testUser.setId(1L);
        Car testCar = new Car("mazda", "miata", 2002, 2000, "test.jpg", 24323, "diesel");
        testCar.setId(1L);
        testCar.setOwner(testUser);

        Mockito.when(carsService.getCarById(1L)).thenReturn(testCar);

        mockMvc.perform(MockMvcRequestBuilders.get("/api/cars/getCar/1")
                .header("Authorization", "Bearer " + this.jwtToken))
            .andExpect(MockMvcResultMatchers.status().isOk())
            .andExpect(MockMvcResultMatchers.jsonPath("$.brand", Matchers.is("mazda")));
    }

    @Test
    @WithMockUser
    public void testGetCarNotFound() throws Exception {
        Mockito.when(carsService.getCarById(1L)).thenThrow(new RepositoryException("Car not found"));

        mockMvc.perform(MockMvcRequestBuilders.get("/api/cars/getCar/1")
                .header("Authorization", "Bearer " + this.jwtToken))
            .andExpect(MockMvcResultMatchers.status().isNotFound());
    }

    @Test
    @WithMockUser
    public void testUpdateCarSuccess() throws Exception {
        User testUser = new User("test", "test", "test", "test");
        testUser.setId(1L);
        Car testCar = new Car("mazda", "miata", 2002, 2000, "test.jpg", 24323, "diesel");
        testCar.setOwner(testUser);
        testCar.setId(1L);

        Mockito.when(carsService.getCarById(1L)).thenReturn(testCar);

        mockMvc.perform(MockMvcRequestBuilders.put("/api/cars/updateCar")
                .header("Authorization", "Bearer " + this.jwtToken)
                .contentType("application/json")
                .content(objectMapper.writeValueAsString(testCar))
            )
            .andExpect(MockMvcResultMatchers.status().isOk());
    }

    @Test
    @WithMockUser(username = "narcis@email.com",authorities = "MANAGER")
    public void testUpdateCarNotFound() throws Exception {
        User testUser = new User("narcis@email.com", "test", "test", "test");
        Car testCar = new Car("mazda", "miata", 2002, 2000, "test.jpg", 24323, "diesel");
        testCar.setOwner(testUser);
        testCar.setId(1L);

        Mockito.when(carsService.getCarById(1L)).thenThrow(new RepositoryException("Car not found"));

        mockMvc.perform(MockMvcRequestBuilders.put("/api/cars/updateCar")
                .header("Authorization", "Bearer " + this.jwtToken)
                .contentType("application/json")
                .content(objectMapper.writeValueAsString(testCar))
            )
            .andExpect(MockMvcResultMatchers.status().isBadRequest());
    }

    @Test
    public void testGetCarsByOwnerIdSuccess() throws Exception {
        User testUser = new User("test", "test", "test", "test");
        Car testCar = new Car("mazda", "miata", 2002, 2000, "test.jpg", 24323, "diesel");
        testCar.setOwner(testUser);

        Mockito.when(carsService.getAllCarsByOwnerId(1L)).thenReturn(List.of(testCar));

        mockMvc.perform(MockMvcRequestBuilders.get("/api/cars/getAllByOwnerId/1")
                .header("Authorization", "Bearer " + this.jwtToken))
            .andExpect(MockMvcResultMatchers.status().isOk())
            .andExpect(MockMvcResultMatchers.jsonPath("$[0].brand", Matchers.is("mazda")));
    }
}
