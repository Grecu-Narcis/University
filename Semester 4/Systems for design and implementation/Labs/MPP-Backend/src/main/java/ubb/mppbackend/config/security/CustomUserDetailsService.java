package ubb.mppbackend.config.security;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import ubb.mppbackend.models.role.Role;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.Collection;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * This service class implements the UserDetailsService interface to load user-specific data
 * from the database for Spring Security authentication and authorization purposes.
 */
@Service
public class CustomUserDetailsService implements UserDetailsService {
    private final UsersRepositoryJPA usersRepository;

    /**
     * Constructs a new CustomUserDetailsService with the provided UsersRepositoryJPA instance.
     *
     * @param usersRepository the repository used to retrieve user data from the database
     */
    @Autowired
    public CustomUserDetailsService(UsersRepositoryJPA usersRepository) {
        this.usersRepository = usersRepository;
    }

    /**
     * Loads the UserDetails for the given email (username) from the database.
     * If the user is not found, a UsernameNotFoundException is thrown.
     *
     * @param email the email (username) of the user to load
     * @return UserDetails object representing the authenticated user
     * @throws UsernameNotFoundException if the user with the specified email is not found
     */
    @Override
    public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
        User requiredUser = usersRepository.findByEmail(email).orElseThrow(() -> new UsernameNotFoundException("Email not found!"));

        return new org.springframework.security.core.userdetails.User(
            requiredUser.getEmail(),
            requiredUser.getPassword(),
            this.mapRolesToAuthorities(requiredUser.getRoles())
        );
    }

    /**
     * Maps the roles of a user to a collection of GrantedAuthority objects
     * for use in Spring Security.
     *
     * @param roles the roles assigned to the user
     * @return a collection of GrantedAuthority objects representing the user's roles
     */
    private Collection<GrantedAuthority> mapRolesToAuthorities(Set<Role> roles) {
        return roles.stream()
            .map(role -> new SimpleGrantedAuthority(role.getName()))
            .collect(Collectors.toList());
    }
}
