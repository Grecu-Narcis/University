package ubb.mppbackend.models.user;

import com.github.javafaker.Faker;
import com.github.javafaker.Name;
import ubb.mppbackend.models.role.Role;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

/**
 * Utility class to generate and save fake User data into a UsersRepository using JPA.
 */
@SuppressWarnings("unused")
public class UserMockGenerator {
    /**
     * Generates a specified number of fake User records and saves them into the provided UsersRepository.
     *
     * @param numberOfUsers    The number of fake User records to generate.
     * @param usersRepository  The UsersRepositoryJPA instance where generated users will be saved.
     * @return                 A list containing the generated fake User records.
     */
    public static List<User> generateFakeData(int numberOfUsers, UsersRepositoryJPA usersRepository) {
        List<User> fakeUsers = new ArrayList<>();

        Role mockUserRole = new Role();
        mockUserRole.setId(2L);
        mockUserRole.setName("MANAGER");

        System.out.println("start");
        for (int i = 0; i < numberOfUsers; i++) {
            User fakeUser = generateFakeUser();
            fakeUser.setRoles(Set.of(mockUserRole));
            fakeUsers.add(fakeUser);

            if ((i + 1) % 1000 == 0)
            {
                System.out.println("saving batch of 1000");
                usersRepository.saveAll(fakeUsers);
                fakeUsers.clear();
            }
        }

        System.out.println("end");
        usersRepository.saveAll(fakeUsers);
        return fakeUsers;
    }

    /**
     * Generates a single fake User record with random data.
     *
     * @return  A new User object populated with fake data.
     */
    private static User generateFakeUser() {
        Faker fakerUserGenerator = new Faker();
        Name fakeName = fakerUserGenerator.name();
        String fakeEmail = fakerUserGenerator.internet().emailAddress();
        String fakePassword = fakerUserGenerator.internet().password();

        return new User(fakeName.lastName(), fakeName.firstName(), fakeEmail, fakePassword);
    }
}
