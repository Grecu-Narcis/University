//package ubb.mppbackend.test_repositories;
//
//import org.junit.jupiter.api.Assertions;
//import org.junit.jupiter.api.Test;
//import ubb.mppbackend.exceptions.RepositoryException;
//import ubb.mppbackend.models.user.User;
//import ubb.mppbackend.repositories.UsersRepository;
//
//import java.util.UUID;
//
//public class UsersRepositoryTests {
//    private final UsersRepository usersRepository;
//
//    public UsersRepositoryTests() {
//        this.usersRepository = new UsersRepository();
//    }
//
//    @Test
//    public void testGetUserById() throws Exception {
//        User userToFind = this.usersRepository.getAll().get(0);
//        //User foundUser = this.usersRepository.getUserById(userToFind.getId());
//
//        //Assertions.assertEquals(userToFind, foundUser);
//    }
//
//    @Test
//    public void testGetUserByIdThrowsException() {
//        Assertions.assertThrows(RepositoryException.class, () -> this.usersRepository.getUserById(UUID.randomUUID()));
//    }
//
//    @Test
//    public void testAddUser() throws Exception {
//        User userToAdd = new User("test", "user", "test.url", 20);
//
//        this.usersRepository.addUser(userToAdd);
//        //Assertions.assertEquals(userToAdd, this.usersRepository.getUserById(userToAdd.getId()));
//    }
//
//    @Test
//    public void testUpdateUser() throws Exception {
//        User userToUpdate = this.usersRepository.getAll().get(0);
//        userToUpdate.setAge(45);
//        userToUpdate.setId((long) 2);
//
//        this.usersRepository.updateUser(userToUpdate);
//        User updatedUser = this.usersRepository.getAll().get(0);
//        Assertions.assertEquals(updatedUser.getAge(), 45);
//    }
//
//    @Test
//    public void testDeleteUser() {
//        User userToDelete = this.usersRepository.getAll().get(0);
//        //this.usersRepository.deleteUser(userToDelete.getId());
//
//        //Assertions.assertThrows(RepositoryException.class, () -> this.usersRepository.getUserById(userToDelete.getId()));
//    }
//
//    @Test
//    public void testGetPage() {
//        Assertions.assertEquals(this.usersRepository.getPage(1, true, 5).size(), 5);
//        Assertions.assertEquals(this.usersRepository.getPage(1, false, 5).size(), 5);
//    }
//
//    @Test
//    public void testGetAll() {
//        Assertions.assertEquals(this.usersRepository.getAll().size(), 10);
//    }
//}
