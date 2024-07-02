package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ubb.mppbackend.models.role.Role;
import ubb.mppbackend.repositories.RoleRepositoryJPA;

import java.util.Optional;

@Service
public class RoleService {
    private final RoleRepositoryJPA roleRepositoryJPA;

    @Autowired
    public RoleService(RoleRepositoryJPA roleRepositoryJPA) {
        this.roleRepositoryJPA = roleRepositoryJPA;
    }

    public Optional<Role> findByName(String roleName) {
        return this.roleRepositoryJPA.findByName(roleName);
    }
}
