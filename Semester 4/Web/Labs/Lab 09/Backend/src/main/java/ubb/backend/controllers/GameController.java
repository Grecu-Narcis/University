package ubb.backend.controllers;

import org.springframework.web.bind.annotation.*;
import ubb.backend.dtos.AddMoveRequest;
import ubb.backend.dtos.UpdateTimeSpentRequest;
import ubb.backend.models.DBManager;

@RestController
@RequestMapping("/api/game")
@CrossOrigin(origins = "*")
public class GameController {
    @PostMapping("/addMove")
    public void addMove(@RequestBody AddMoveRequest addMoveRequest) {
        DBManager.addMove(addMoveRequest.moveDirection, addMoveRequest.userId);
    }

    @PutMapping("/updateTimeSpent")
    public void updateTimeSpent(@RequestBody UpdateTimeSpentRequest updateTimeSpentRequest) {
        System.out.println(updateTimeSpentRequest.userId);
        DBManager.updateTimeSpent(updateTimeSpentRequest.userId, updateTimeSpentRequest.newTime);
    }
}
