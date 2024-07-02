package ubb.mppbackend.business;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.mail.MailException;
import org.springframework.mail.SimpleMailMessage;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

/**
 * Service class responsible for sending emails asynchronously using JavaMailSender.
 */
@Service
public class EmailService {
    /** The mail sender object used for sending emails. */
    private final JavaMailSender mailSender;

    /** Maximum number of retry attempts in case of email sending failure. */
    private static final int MAX_RETRY_ATTEMPTS = 3;

    /** Delay (in milliseconds) between retry attempts. */
    private static final int RETRY_DELAY_MS = 2000; // 2 seconds

    /**
     * Constructor for EmailService.
     * @param mailSender The JavaMailSender object used for sending emails.
     */
    @Autowired
    public EmailService(JavaMailSender mailSender) {
        this.mailSender = mailSender;
    }

    /**
     * Asynchronously sends an email with the given parameters.
     * If sending fails, it retries according to a predefined number of attempts and delay.
     * @param destinationMail The email address of the recipient.
     * @param mailSubject The subject of the email.
     * @param mailBody The body content of the email.
     */
    @Async
    public void sendEmail(String destinationMail, String mailSubject, String mailBody) {
        int currentAttempt = 0;
        boolean isSent = false;

        while (currentAttempt < EmailService.MAX_RETRY_ATTEMPTS && !isSent) {
            try {
                SimpleMailMessage messageToSend = this.createMail(destinationMail, mailSubject, mailBody);
                mailSender.send(messageToSend);
                isSent = true;
            }
            catch (MailException mailException) {
                currentAttempt++;

                if (currentAttempt < EmailService.MAX_RETRY_ATTEMPTS) {
                    try {
                        Thread.sleep(EmailService.RETRY_DELAY_MS);
                    }
                    catch (InterruptedException interruptedException) {
                        Thread.currentThread().interrupt();
                        break;
                    }
                }
            }
        }
    }

    /**
     * Creates a SimpleMailMessage object with the provided email parameters.
     * @param destinationMail The email address of the recipient.
     * @param mailSubject The subject of the email.
     * @param mailBody The body content of the email.
     * @return A SimpleMailMessage object containing the email details.
     */
    private SimpleMailMessage createMail(String destinationMail, String mailSubject, String mailBody) {
        SimpleMailMessage messageToSend = new SimpleMailMessage();

        messageToSend.setTo(destinationMail);
        messageToSend.setSubject(mailSubject);
        messageToSend.setText(mailBody);

        return messageToSend;
    }
}
