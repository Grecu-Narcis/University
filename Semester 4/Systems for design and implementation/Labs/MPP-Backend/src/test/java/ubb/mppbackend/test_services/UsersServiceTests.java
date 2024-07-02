package ubb.mppbackend.test_services;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.data.domain.*;
import ubb.mppbackend.business.UsersService;
import ubb.mppbackend.dto.UserDTO;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@SpringBootTest
public class UsersServiceTests {
    @MockBean
    UsersRepositoryJPA usersRepositoryJPA;

    private UsersService usersService;

    @BeforeEach
    public void setUp() {
        this.usersService = new UsersService(usersRepositoryJPA, null);
    }

    @Test
    public void testGetUserByIdSuccess() throws Exception {
        User userToFind = new User("test", "test", "test", "test");
        userToFind.setId((long) 1);
        Mockito.when(this.usersRepositoryJPA.findById(userToFind.getId())).thenReturn(java.util.Optional.of(userToFind));

        Long idToSearch = this.usersService.getById(userToFind.getId()).getId();
        Assertions.assertEquals(this.usersService.getById(idToSearch).getId(), idToSearch);
    }

    @Test
    public void testGetUserByIdFails() {
        Long idToSearch = (long) -1;
        Mockito.when(this.usersRepositoryJPA.findById(idToSearch)).thenReturn(java.util.Optional.empty());
        Assertions.assertThrows(RepositoryException.class, () -> this.usersService.getById(idToSearch));
    }

    @Test
    public void testAddUser() throws Exception {
        User userToAdd = new User("test", "user", "test.url", "test");
        userToAdd.setId((long) 1);

        Mockito.when(this.usersRepositoryJPA.save(userToAdd)).thenReturn(userToAdd);
        Mockito.when(this.usersRepositoryJPA.findById(userToAdd.getId())).thenReturn(Optional.of(userToAdd));
        this.usersService.addUser(userToAdd);

        User foundUser = this.usersService.getById(userToAdd.getId());

        Assertions.assertEquals(userToAdd, foundUser);
    }

    @Test
    public void testUpdateUserSuccess() {
        User testUser = new User("test", "test", "test", "test");
        testUser.setId((long) 2);

        Mockito.when(this.usersRepositoryJPA.findById(testUser.getId())).thenReturn(Optional.of(testUser));
        Mockito.when(this.usersRepositoryJPA.save(testUser)).thenReturn(testUser);

        UserDTO userDTO = new UserDTO(2L, "test", "test", "test", "User");

        try {
            this.usersService.updateUser(userDTO);
        }

        catch (Exception ignored) {}
    }

    @Test
    public void testUpdateUserThrowsException() {
        User userToUpdate = new User("test", "user", "test.url", "test");
        UserDTO userDTO = new UserDTO(2L, "test", "test", "test", "User");

        Mockito.when(this.usersRepositoryJPA.findById(Mockito.anyLong())).thenReturn(Optional.empty());
        Assertions.assertThrows(RepositoryException.class, () -> this.usersService.updateUser(userDTO));
    }

    @Test
    public void testDeleteUser() {
        User userToDelete = new User("test", "test", "test", "test");
        userToDelete.setId((long) 2);

        Mockito.when(this.usersRepositoryJPA.findById(userToDelete.getId())).thenReturn(Optional.empty());

        this.usersService.deleteUser(userToDelete.getId());
        Assertions.assertThrows(RepositoryException.class, () -> this.usersService.getById(userToDelete.getId()));
    }

    @Test
    public void testGetPageAscending() {
        List<User> demoUsers = new ArrayList<>();
        demoUsers.add(new User("test1", "test1", "test1", "test"));
        demoUsers.add(new User("test2", "test2", "test2", "test"));
        demoUsers.add(new User("test3", "test3", "test3", "test"));

        Sort sortAscending = Sort.by(Sort.Direction.ASC, "id");
        Pageable requestedPageAscending = PageRequest.of(1, 3, sortAscending);
        Page<User> returnPageAscending = new PageImpl<>(demoUsers, requestedPageAscending, demoUsers.size());

        Mockito.when(this.usersRepositoryJPA.findAll(requestedPageAscending)).thenReturn(returnPageAscending);

        Assertions.assertEquals(this.usersService.getPage(1, true, 3).size(), 3);
    }

    @Test
    public void testGetPageDescending() {
        List<User> demoUsers = new ArrayList<>();
        demoUsers.add(new User("test1", "test1", "test1", "test"));
        demoUsers.add(new User("test2", "test2", "test2", "test"));
        demoUsers.add(new User("test3", "test3", "test3", "test"));


        Sort sortDescending = Sort.by(Sort.Direction.DESC, "id");
        Pageable requestedPageDescending = PageRequest.of(1, 3, sortDescending);
        Page<User> returnPageDescending = new PageImpl<>(demoUsers, requestedPageDescending, demoUsers.size());

        Mockito.when(this.usersRepositoryJPA.findAll(requestedPageDescending)).thenReturn(returnPageDescending);

        Assertions.assertEquals(this.usersService.getPage(1, false, 3).size(), 3);
    }

    @Test
    public void testGetAll() {
        Mockito.when(this.usersRepositoryJPA.findAll()).thenReturn(new ArrayList<>());

        Assertions.assertEquals(this.usersService.getAll().size(), 0);
    }
}
