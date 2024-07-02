package ubb.mppbackend.config.security;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.config.annotation.authentication.configuration.AuthenticationConfiguration;
import org.springframework.security.config.annotation.method.configuration.EnableMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configurers.AbstractHttpConfigurer;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

/**
 * Configuration class for setting up security in the application.
 */
@Configuration
@EnableWebSecurity
@EnableMethodSecurity
public class SecurityConfig {
    private final JWTAuthenticationEntryPoint authenticationEntryPoint;
    private final CustomAccessDeniedHandler customAccessDeniedHandler;
    private final CustomUserDetailsService userDetailsService;

    /**
     * Constructor for SecurityConfig.
     *
     * @param userDetailsService        CustomUserDetailsService implementation for user details management.
     * @param authenticationEntryPoint   JWTAuthenticationEntryPoint for handling authentication errors.
     * @param customAccessDeniedHandler CustomAccessDeniedHandler for handling access denied errors.
     */
    @Autowired
    public SecurityConfig(CustomUserDetailsService userDetailsService,
                          JWTAuthenticationEntryPoint authenticationEntryPoint,
                          CustomAccessDeniedHandler customAccessDeniedHandler) {
        this.userDetailsService = userDetailsService;
        this.authenticationEntryPoint = authenticationEntryPoint;
        this.customAccessDeniedHandler = customAccessDeniedHandler;
    }

    /**
     * Configures the security filter chain with custom settings.
     *
     * @param http HttpSecurity object to configure security settings.
     * @return SecurityFilterChain configured for the application.
     * @throws Exception if configuration encounters an error.
     */
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .csrf(AbstractHttpConfigurer::disable)
            .exceptionHandling(exceptionHandling ->
                exceptionHandling
                    .accessDeniedHandler(this.customAccessDeniedHandler)
                    .authenticationEntryPoint(this.authenticationEntryPoint))
            .sessionManagement(sessionManagement -> sessionManagement.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/api/auth/login",
                    "/api/auth/register",
                    "/api/users/ping",
                    "/api/car-dealers/**",
                    "/websocket/**",
                    "api/ai/**",
                    "api/location/**",
                    "api/cars/getPageByOwnerId",
                    "api/cars/getCarsCount/**",
                    "api/cars/getCar/**").permitAll()
                .anyRequest().authenticated());

        http.addFilterBefore(jwtAuthenticationFilter(), UsernamePasswordAuthenticationFilter.class);

        return http.build();
    }

    /**
     * Configures the AuthenticationManager bean.
     *
     * @param authenticationConfiguration AuthenticationConfiguration instance.
     * @return AuthenticationManager bean for managing authentication requests.
     * @throws Exception if configuration encounters an error.
     */
    @Bean
    public AuthenticationManager authenticationManager(AuthenticationConfiguration authenticationConfiguration) throws Exception {
        return authenticationConfiguration.getAuthenticationManager();
    }

    /**
     * Configures the password encoder bean for encoding user passwords.
     *
     * @return PasswordEncoder bean using BCryptPasswordEncoder.
     */
    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    /**
     * Creates the JWTAuthenticationFilter bean for handling JWT authentication.
     *
     * @return JWTAuthenticationFilter bean configured for processing JWT authentication.
     */
    @Bean
    public JWTAuthenticationFilter jwtAuthenticationFilter() {
        return new JWTAuthenticationFilter();
    }
}
