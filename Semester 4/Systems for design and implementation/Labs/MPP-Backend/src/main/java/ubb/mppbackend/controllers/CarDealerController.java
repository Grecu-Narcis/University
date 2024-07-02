package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ubb.mppbackend.business.CarDealerService;
import ubb.mppbackend.business.UsersService;
import ubb.mppbackend.dto.UserDTO;
import ubb.mppbackend.exceptions.RepositoryException;
import ubb.mppbackend.models.user.User;

import java.util.List;

@RestController
@RequestMapping("/api/car-dealers")
@CrossOrigin(origins = "*")
public class CarDealerController {
    private final CarDealerService carDealerService;
    private final UsersService usersService;

    @Autowired
    public CarDealerController(CarDealerService carDealerService, UsersService usersService) {
        this.carDealerService = carDealerService;
        this.usersService = usersService;
    }

    @GetMapping("/getPage")
    public ResponseEntity<List<UserDTO>> getPage(@RequestParam(name = "page") Integer requiredPage,
                                                 @RequestParam(name = "size") Integer pageSize) {
        try {
            return ResponseEntity.ok().body(this.carDealerService.getPage(requiredPage, pageSize));
        }
        catch (Exception e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
        }
    }

    @GetMapping("/getPageByName")
    public ResponseEntity<List<UserDTO>> getPageFilteredByName(@RequestParam(name = "page") Integer requiredPage,
                                                               @RequestParam(name = "size") Integer pageSize,
                                                               @RequestParam(name = "name") String userName) {
        try {
            return ResponseEntity.ok().body(this.carDealerService.getPageFilteredByName(requiredPage, pageSize, userName));
        }
        catch (Exception e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
        }
    }

    @GetMapping("/getCountByName")
    public ResponseEntity<Long> getCountByName(@RequestParam(name = "name") String userName) {
        try {
            return ResponseEntity.ok().body(this.carDealerService.getCountByName(userName));
        }
        catch (Exception e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
        }
    }

    @GetMapping("/getDealer/{userId}")
    public ResponseEntity<UserDTO> getDealer(@PathVariable String userId) {
        try {
            User requiredUser = this.usersService.getById(Long.parseLong(userId));
            UserDTO requiredUserDTO = new UserDTO(requiredUser);

            return ResponseEntity.ok().body(requiredUserDTO);
        }

        catch (RepositoryException e) {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/getAll")
    public ResponseEntity<List<UserDTO>> getAll() {
        return ResponseEntity.ok().body(this.carDealerService.getAll());
    }

    @GetMapping("/getCount")
    public ResponseEntity<Long> getCount() {
        return ResponseEntity.ok().body(this.carDealerService.getCount());
    }
}
