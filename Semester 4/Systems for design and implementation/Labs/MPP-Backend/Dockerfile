# Build
FROM maven:3.8.3-openjdk-17 AS build
WORKDIR /app
COPY ./src /src
COPY pom.xml .
RUN mvn -f ./pom.xml clean package

# Run
FROM openjdk:17
COPY ./target/MPP-Backend-0.0.1-SNAPSHOT.jar ./target/MPP-Backend-0.0.1-SNAPSHOT.jar
COPY ./src/main/resources/profile-images ./src/main/resources/profile-images

EXPOSE 8443
USER root
CMD ["java","-jar","./target/MPP-Backend-0.0.1-SNAPSHOT.jar"]