package ubb.mppbackend;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.scheduling.annotation.EnableAsync;
import org.springframework.scheduling.annotation.EnableScheduling;

//@SpringBootApplication(exclude = {DataSourceAutoConfiguration.class})
@SpringBootApplication(scanBasePackages = "ubb.mppbackend")
@EnableScheduling
@EnableAsync
@EntityScan(basePackages = "ubb.mppbackend.models")
public class MppBackendApplication {
    public static void main(String[] args) {
        SpringApplication.run(MppBackendApplication.class, args);
    }
}
