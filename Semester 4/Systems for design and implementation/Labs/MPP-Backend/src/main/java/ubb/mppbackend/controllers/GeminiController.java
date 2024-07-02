package ubb.mppbackend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.reactive.function.client.WebClient;
import reactor.core.publisher.Mono;
import ubb.mppbackend.dto.PromptDTO;
import ubb.mppbackend.dto.RequestDTO;
import ubb.mppbackend.models.car.Car;
import ubb.mppbackend.repositories.CarsRepositoryJPA;

import java.util.Optional;

@RestController
@RequestMapping("/api/ai")
public class GeminiController {
    @Value("${AI_IP}")
    private String aiMicroserviceHost;
    private final CarsRepositoryJPA carsRepositoryJPA;

    @Autowired
    public GeminiController(CarsRepositoryJPA carsRepositoryJPA) {
        this.carsRepositoryJPA = carsRepositoryJPA;
    }

    @PostMapping("/generate")
    public ResponseEntity<?> generatePromptResponse(@RequestBody PromptDTO promptRequest) {
        Optional<Car> requiredCar = this.carsRepositoryJPA.findById(Long.parseLong(promptRequest.getCarId()));

        if (requiredCar.isEmpty()) return ResponseEntity.ok().body("Sorry, I encountered an error!");

        String textPrompt = this.getPromptFromCar(requiredCar.get(), promptRequest.getMessage());
        String promptResult = this.getAnswer(textPrompt);

        return ResponseEntity.ok().body(promptResult);
    }

    private String getAnswer(String textPrompt) {
        try {
            var request = new RequestDTO(textPrompt);

            WebClient webClient = WebClient.builder()
                .baseUrl(this.aiMicroserviceHost)
                .build();

            return webClient.post()
                .uri("/prompt")
                .contentType(MediaType.APPLICATION_JSON)
                .body(Mono.just(request), RequestDTO.class)
                .retrieve()
                .bodyToMono(String.class)
                .block();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return "Sorry, I cannot answer right now!";
        }
    }

    private String getPromptFromCar(Car requiredCar, String question) {
        return String.format("""
                Given the following car information, answer the question. Answer in maximum 200 words.
                The car provided is from a dealer. You are talking with the client.
                Give a response without expecting extra info. Answer based on the given question and nothing more.
                Avoid any formatting on the response. Use only letters and digits!
                If the question is not related to the given car, answer with 'Sorry, I am here to assist you about this car. How can I help you?'
                Answer like you are a car specialist. Don't give answers like we cannot know!
                Car: brand: %s, model: %s, mileage: %d, fuel type: %s, manufacturing year: %d.
                Question: %s
                """, requiredCar.getBrand(), requiredCar.getModel(), requiredCar.getMileage(),
            requiredCar.getFuelType(), requiredCar.getYear(), question);
    }
}
