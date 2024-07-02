package ubb.mppbackend.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
public class SendMailDTO {
    private String userName;
    private String userEmail;
    private String message;
    private String destination;
}
