package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ubb.mppbackend.business.DealerLocationService;
import ubb.mppbackend.dto.UpdateLocationDTO;

@RestController
@RequestMapping("/api/location")
@CrossOrigin(origins = "*")
public class DealerLocationController {
    private final DealerLocationService dealerLocationService;

    @Autowired
    public DealerLocationController(DealerLocationService dealerLocationService) {
        this.dealerLocationService = dealerLocationService;
    }

    @GetMapping("/get/{id}")
    public ResponseEntity<?> getDealerLocation(@PathVariable("id") long dealerId) {
        try {
            return ResponseEntity.ok().body(this.dealerLocationService.getDealerLocation(dealerId));
        }
        catch (Exception e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }

    @PutMapping("/update")
    public void updateDealerLocation(@RequestBody UpdateLocationDTO request) {
        this.dealerLocationService.updateDealerLocation(request.getDealerId(), request.getLatitude(), request.getLongitude());
    }
}
