package ubb.mppbackend.models.user;

import jakarta.persistence.*;
import lombok.*;
import ubb.mppbackend.models.car.Car;
import ubb.mppbackend.models.role.Role;

import java.util.List;
import java.util.Set;

/**
 * Represents a user entity with basic information.
 * This entity is mapped to the "users" table in the database.
 */
@Getter
@Setter
@ToString
@NoArgsConstructor
@Entity(name = "users")
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", updatable = false)
    private Long id;

    @Column(name = "first_name", nullable = false, length = 50)
    private String firstName;

    @Column(name = "last_name", nullable = false, length = 50)
    private String lastName;

    @Column(name="email", nullable = false)
    private String email;

    @Column(name="password", nullable = false)
    private String password;

    @OneToMany(mappedBy = "owner", fetch = FetchType.LAZY, cascade = CascadeType.REMOVE)
    private List<Car> cars;

    @OneToOne(mappedBy = "user", fetch = FetchType.LAZY, cascade = CascadeType.REMOVE)
    private ProfileImage profileImage;

    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(
        name = "users_roles",
        joinColumns = @JoinColumn(name = "user_id"),
        inverseJoinColumns = @JoinColumn(name = "role_id")
    )
    private Set<Role> roles;
    /**
     * Constructs a new User with the specified details.
     *
     * @param firstName  The first name of the user.
     * @param lastName   The last name of the user.
     * @param email      The email address of the user.
     * @param password   The password of the user.
     */
    public User(String firstName, String lastName, String email, String password) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.password = password;
    }

    /**
     * Updates the user's information based on the provided newUser object.
     *
     * @param newUser The new User object containing updated information.
     */
    public void update(User newUser) {
        this.setFirstName(newUser.getFirstName());
        this.setLastName(newUser.getLastName());
        this.setEmail(newUser.getEmail());
        this.setPassword(newUser.getPassword());
    }

    /**
     * Compares this User object with another object for equality based on ID.
     *
     * @param obj The object to compare with.
     * @return true if the objects are equal (i.e., have the same ID), otherwise false.
     */
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof User userToCompare))
            return false;

        return this.getId().equals(userToCompare.getId());
    }
}
