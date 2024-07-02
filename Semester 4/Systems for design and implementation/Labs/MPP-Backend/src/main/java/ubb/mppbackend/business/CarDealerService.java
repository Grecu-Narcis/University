package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import ubb.mppbackend.dto.UserDTO;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class CarDealerService {
    private final UsersRepositoryJPA usersRepositoryJPA;

    @Autowired
    public CarDealerService(UsersRepositoryJPA usersRepositoryJPA) {
        this.usersRepositoryJPA = usersRepositoryJPA;
    }

    public List<UserDTO> getPage(int requiredPage, int pageSize) {
        Pageable pageableRequest = PageRequest.of(requiredPage, pageSize);

        return this.usersRepositoryJPA
            .findAllByRole("MANAGER", pageableRequest)
            .stream()
            .map(UserDTO::new)
            .collect(Collectors.toList());
    }

    public List<UserDTO> getAll() {
        return this.usersRepositoryJPA.findAllByRole("MANAGER")
            .stream()
            .map(UserDTO::new)
            .collect(Collectors.toList());
    }

    public Long getCount() {
        return this.usersRepositoryJPA.countAllByRole("MANAGER");
    }

    public List<UserDTO> getPageFilteredByName(Integer requiredPage, Integer pageSize, String userName) {
        Pageable pageableRequest = PageRequest.of(requiredPage, pageSize);

        return this.usersRepositoryJPA.findAllByRoleAndUserName("MANAGER", userName, pageableRequest)
            .stream()
            .map(UserDTO::new)
            .collect(Collectors.toList());
    }

    public Long getCountByName(String userName) {
        return this.usersRepositoryJPA.countAllByRoleAndUserName("MANAGER", userName);
    }
}
