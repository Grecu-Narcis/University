package ubb.mppbackend.models.user;


import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

/**
 * Represents a profile image associated with a user.
 * This entity is mapped to the "profile_images" table in the database.
 */
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Entity(name = "profile_images")
public class ProfileImage {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String imageUrl;

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "user_id")
    private User user;

    /**
     * Constructs a new ProfileImage with the specified image URL and associated User.
     *
     * @param imageUrl The URL of the profile image.
     * @param owner    The User who owns this profile image.
     */
    public ProfileImage(String imageUrl, User owner) {
        this.imageUrl = imageUrl;
        this.user = owner;
    }
}
