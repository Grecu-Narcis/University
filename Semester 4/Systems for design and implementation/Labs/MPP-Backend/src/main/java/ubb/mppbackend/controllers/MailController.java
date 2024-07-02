package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import ubb.mppbackend.business.EmailService;
import ubb.mppbackend.dto.SendMailDTO;

@RestController
@RequestMapping("/api/mail")
public class MailController {
    private final EmailService emailService;

    @Autowired
    public MailController(EmailService emailService) {
        this.emailService = emailService;
    }

    @PostMapping("/send")
    public void sendMail(@RequestBody SendMailDTO mailDTO) {
        String mailBody = String.format("""
            Received from: %s with email: %s.
            Message: %s
            """, mailDTO.getUserName(), mailDTO.getUserEmail(), mailDTO.getMessage());

        this.emailService.sendEmail(mailDTO.getDestination(), "New message", mailBody);
    }
}
