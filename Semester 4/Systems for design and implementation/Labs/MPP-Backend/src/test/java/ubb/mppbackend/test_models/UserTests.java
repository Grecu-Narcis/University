package ubb.mppbackend.test_models;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import ubb.mppbackend.models.user.User;

public class UserTests {
    @Test
    public void testGetId() {
        User user = new User("test", "test", "test", "test");
        Long id = user.getId();
        Assertions.assertEquals(user.getId(), id);
    }

    @Test
    public void testGetFirstName() {
        User user = new User("test", "test", "test", "test");
        String firstName = user.getFirstName();
        Assertions.assertEquals(user.getFirstName(), firstName);
    }

    @Test
    public void testSetFirstName() {
        User user = new User("test", "test", "test", "test");
        user.setFirstName("newTest");
        Assertions.assertEquals(user.getFirstName(), "newTest");
    }

    @Test
    public void testGetLastName() {
        User user = new User("test", "test", "test", "test");
        String lastName = user.getLastName();
        Assertions.assertEquals(user.getLastName(), lastName);
    }

    @Test
    public void testSetLastName() {
        User user = new User("test", "test", "test", "test");
        user.setLastName("newTest");
        Assertions.assertEquals(user.getLastName(), "newTest");
    }

    @Test
    public void testGetPassword() {
        User user = new User("test", "test", "test", "test");
        String userPassword = user.getPassword();
        Assertions.assertEquals(user.getPassword(), userPassword);
    }

    @Test
    public void testSetPassword() {
        User user = new User("test", "test", "test", "test");
        user.setPassword("newTest");
        Assertions.assertEquals(user.getPassword(), "newTest");
    }

    @Test
    public void testUpdate() {
        User user = new User("test", "test", "test", "test");
        User newUser = new User("newTest", "newTest", "newTest", "newTest");
        user.update(newUser);
        Assertions.assertEquals(user.getFirstName(), "newTest");
        Assertions.assertEquals(user.getLastName(), "newTest");
        Assertions.assertEquals(user.getPassword(), "newTest");
    }

    @Test
    public void testConstructor() {
        User user = new User("test", "test", "test", "test");
        Assertions.assertEquals(user.getFirstName(), "test");
        Assertions.assertEquals(user.getLastName(), "test");
        Assertions.assertEquals(user.getPassword(), "test");
    }

    @Test
    public void testEqualsSuccess() {
        User user1 = new User("test", "test", "test", "test");
        user1.setId((long) 2);

        Assertions.assertEquals(user1, user1);
    }

    @Test
    public void testEqualsFailure() {
        User user1 = new User("test", "test", "test", "test");
        User user2 = new User("test", "test", "test", "test");
        user1.setId((long) 2);
        user2.setId((long) 3);

        Assertions.assertNotEquals(user1, user2);
        Assertions.assertNotEquals(user1, null);
        Assertions.assertNotEquals(user1, "test");
    }
}
