package ubb.mppbackend.test_controllers;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.context.annotation.Import;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.test.context.support.WithMockUser;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;
import ubb.mppbackend.business.ImagesService;
import ubb.mppbackend.business.RoleService;
import ubb.mppbackend.business.UsersService;
import ubb.mppbackend.config.TestConfig;
import ubb.mppbackend.config.security.*;
import ubb.mppbackend.controllers.UsersController;
import ubb.mppbackend.models.role.Role;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.RoleRepositoryJPA;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.ArrayList;
import java.util.Optional;
import java.util.Set;

@WebMvcTest(UsersController.class)
@Import({TestConfig.class, SecurityConfig.class, JWTAuthenticationEntryPoint.class, CustomAccessDeniedHandler.class,
    RoleService.class})
@AutoConfigureMockMvc
public class UsersControllerTests {
    private final String endPoint = "/api/users";
    @Autowired private MockMvc mockMvc;
    @Autowired private ObjectMapper objectMapper;
    @MockBean private UsersService usersService;
    @MockBean private ImagesService imagesService;
    @MockBean private UsersRepositoryJPA usersRepositoryJPA;
    @MockBean private RoleRepositoryJPA roleRepositoryJPA;
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
            .roles("USER")
            .build();

        Mockito.when(customUserDetailsService.loadUserByUsername("narcis@email.com")).thenReturn(mockUserDetails);
    }

    @Test
    @WithMockUser()
    public void GetUser_WithValidCredentials_ReturnStatusOK() throws Exception {
        Long userId = (long) 1;

        User mockUser = new User("test", "test", "test", "test");
        mockUser.setId(userId);
        Role mockRole = new Role();
        mockRole.setName("USER");

        mockUser.setRoles(Set.of(mockRole));

        Mockito.when(usersService.getById(userId)).
            thenReturn(mockUser);

        mockMvc.perform(MockMvcRequestBuilders.get(endPoint + "/getUser/" + userId)
                .header("Authorization", "Bearer " + this.jwtToken))
            .andExpect(MockMvcResultMatchers.status().isOk())
            .andExpect(MockMvcResultMatchers.jsonPath("$.firstName", Matchers.is("test")));
    }

    @Test
    @WithMockUser(username = "narcis@email.com")
    public void GetUser_NotAuthorized_ReturnsStatusUnauthorized() throws Exception {
        long userId = 5;

        mockMvc.perform(MockMvcRequestBuilders.get(endPoint + "/getUser/" + userId)
                .header("Authorization", "Bearer " + this.jwtToken))
            .andExpect(MockMvcResultMatchers.status().isUnauthorized());
    }

    @Test
    @WithMockUser(username = "narcis@email.com", password = "secret")
    public void GetPage_WithValidCredentials_ReturnStatusOK() throws Exception {
        Mockito.when(usersService.getPage(1, true, 10)).thenReturn(new ArrayList<>());

        mockMvc.perform(MockMvcRequestBuilders.get(
            endPoint + "/getPage?page=1&isAscending=true&pageSize=10")
                .header("Authorization", "Bearer " + this.jwtToken)
            ).andExpect(MockMvcResultMatchers.status().isOk())
            .andExpect(MockMvcResultMatchers.jsonPath("$", Matchers.is(new ArrayList<>())));
    }

    @Test
    @WithMockUser(roles = "USER", authorities = "USER")
    public void GetAll_NonAdminUser_ReturnsStatusForbidden() throws Exception {
        Mockito.when(usersService.getAll()).thenReturn(new ArrayList<>());

        mockMvc.perform(MockMvcRequestBuilders.get(endPoint + "/getAll")
                .header("Authorization", "Bearer " + this.jwtToken))
            .andExpect(MockMvcResultMatchers.status().isForbidden());
    }

//    @Test
//    public void testAddUserSuccess() throws Exception {
//        User user = new User("test", "test", "test", "test");
//        user.setId((long) 2);
//        mockMvc.perform(MockMvcRequestBuilders.post(endPoint + "/addUser")
//            .contentType(MediaType.APPLICATION_JSON)
//            .content(objectMapper.writeValueAsString(user)))
//            .andExpect(MockMvcResultMatchers.status().isOk()).andReturn();
//
//        Mockito.verify(usersService, Mockito.times(1)).addUser(user);
//    }
//
//    @Test
//    public void testAddUserFailsValidator() throws Exception {
//        User user = new User("te", "t", "test", "test");
//        user.setId((long) 2);
//        Mockito.doThrow(UserValidatorException.class).when(usersService).addUser(user);
//
//        mockMvc.perform(MockMvcRequestBuilders.post(endPoint + "/addUser")
//            .contentType(MediaType.APPLICATION_JSON)
//            .content(objectMapper.writeValueAsString(user)))
//            .andExpect(MockMvcResultMatchers.status().isBadRequest());
//    }
//
//    @Test
//    public void testUpdateUserSuccess() throws Exception {
//        User user = new User("test", "test", "test", "test");
//        user.setId((long) 2);
//
//        mockMvc.perform(MockMvcRequestBuilders.put(endPoint + "/updateUser")
//            .contentType(MediaType.APPLICATION_JSON)
//            .content(objectMapper.writeValueAsString(user)))
//            .andExpect(MockMvcResultMatchers.status().isOk()).andReturn();
//
//        Mockito.verify(usersService, Mockito.times(1)).updateUser(user);
//    }
//
//    @Test
//    public void testUpdateUserNotFound() throws Exception {
//        User user = new User("test", "test", "test", "test");
//        user.setId((long) 2);
//
//        Mockito.doThrow(new RepositoryException("User not found!")).when(usersService).updateUser(user);
//
//        mockMvc.perform(MockMvcRequestBuilders.put(endPoint + "/updateUser")
//            .contentType(MediaType.APPLICATION_JSON)
//            .content(objectMapper.writeValueAsString(user)))
//            .andExpect(MockMvcResultMatchers.status().isBadRequest());
//    }
//
//    @Test
//    public void testUpdateUserFailsValidator() throws Exception {
//        User user = new User("test", "test", "test", "test");
//        user.setId((long) 2);
//
//        Mockito.doThrow(UserValidatorException.class).when(usersService).updateUser(user);
//
//        mockMvc.perform(MockMvcRequestBuilders.put(endPoint + "/updateUser")
//            .contentType(MediaType.APPLICATION_JSON)
//            .content(objectMapper.writeValueAsString(user)))
//            .andExpect(MockMvcResultMatchers.status().isBadRequest());
//    }
//
//    @Test
//    public void testDeleteUser() throws Exception {
//        long idToRemove = 2;
//        mockMvc.perform(MockMvcRequestBuilders.delete(endPoint + "/delete/" + idToRemove))
//            .andExpect(MockMvcResultMatchers.status().isOk());
//    }
//
//    @Test
//    public void testGetUsersCount() throws Exception {
//        Mockito.when(usersService.getAll()).thenReturn(new ArrayList<>());
//
//        mockMvc.perform(MockMvcRequestBuilders.get(endPoint + "/countUsers"))
//            .andExpect(MockMvcResultMatchers.status().isOk())
//            .andExpect(MockMvcResultMatchers.jsonPath("$", Matchers.is(0)));
//    }

    @Test
    public void Ping_WhenCalled_ReturnsSuccess() throws Exception {
        mockMvc.perform(MockMvcRequestBuilders.get(endPoint + "/ping"))
            .andExpect(MockMvcResultMatchers.status().isOk());
    }
}

