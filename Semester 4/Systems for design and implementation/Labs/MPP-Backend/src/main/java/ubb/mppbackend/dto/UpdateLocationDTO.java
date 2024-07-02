package ubb.mppbackend.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class UpdateLocationDTO {
    private long dealerId;
    private double latitude;
    private double longitude;
}
