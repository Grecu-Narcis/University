package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ubb.mppbackend.dto.LocationDTO;
import ubb.mppbackend.models.location.DealerLocation;
import ubb.mppbackend.models.user.User;
import ubb.mppbackend.repositories.DealerLocationRepositoryJPA;
import ubb.mppbackend.repositories.UsersRepositoryJPA;

import java.util.Optional;

@Service
public class DealerLocationService {
    private final DealerLocationRepositoryJPA dealerLocationRepositoryJPA;
    private final UsersRepositoryJPA usersRepositoryJPA;

    @Autowired
    public DealerLocationService(DealerLocationRepositoryJPA dealerLocationRepositoryJPA,
                                 UsersRepositoryJPA usersRepositoryJPA) {
        this.dealerLocationRepositoryJPA = dealerLocationRepositoryJPA;
        this.usersRepositoryJPA = usersRepositoryJPA;
    }

    public LocationDTO getDealerLocation(long dealerId) throws Exception {
        Optional<DealerLocation> locationOptional = this.dealerLocationRepositoryJPA.findByUserId(dealerId);

        if (locationOptional.isEmpty()) throw new Exception("No location found!");

        return new LocationDTO(
            locationOptional.get().getLatitude(),
            locationOptional.get().getLongitude()
        );
    }

    public void updateDealerLocation(long dealerId, double newLatitude, double newLongitude) {
        Optional<DealerLocation> locationOptional = this.dealerLocationRepositoryJPA.findByUserId(dealerId);
        Optional<User> requiredDealer = this.usersRepositoryJPA.findById(dealerId);

        if (requiredDealer.isEmpty()) return;

        DealerLocation updatedLocation = new DealerLocation();
        updatedLocation.setUser(requiredDealer.get());

        if (locationOptional.isPresent()) updatedLocation = locationOptional.get();

        updatedLocation.setLatitude(newLatitude);
        updatedLocation.setLongitude(newLongitude);

        this.dealerLocationRepositoryJPA.save(updatedLocation);
    }
}
