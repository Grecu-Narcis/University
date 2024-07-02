package ubb.mppbackend.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class CorsConfig implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**") // Apply CORS configuration to specific path patterns
            .allowedOriginPatterns("*") // Allow requests from this origin
            .allowedMethods("*") // Allow only specified HTTP methods
            .allowedHeaders("*"); // Allow only specified headers
    }

}
