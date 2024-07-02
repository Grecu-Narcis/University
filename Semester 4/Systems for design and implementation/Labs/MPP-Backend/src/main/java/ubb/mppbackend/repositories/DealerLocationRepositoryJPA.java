package ubb.mppbackend.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ubb.mppbackend.models.location.DealerLocation;

import java.util.Optional;

@Repository
public interface DealerLocationRepositoryJPA extends JpaRepository<DealerLocation, Long> {
    Optional<DealerLocation> findByUserId(Long userId);
}
