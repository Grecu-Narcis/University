package view;

import controller.Controller;
import exceptions.RepositoryException;
import models.*;

import java.util.ArrayList;
import java.util.Scanner;

public class View {
    private Controller vehiclesController;

    public View(Controller ctrl) {
        vehiclesController = ctrl;
    }

    private final Scanner inScanner = new Scanner(System.in);

    private void printMenu() {
        System.out.println("Press 0 to exit!");
        System.out.println("Press 1 to add a vehicle!");
        System.out.println("Press 2 to remove a vehicle!");
        System.out.println("Press 3 to print all!");
        System.out.println("Press 4 to filter!");
    }

    private void addVehicleMenu() throws RepositoryException {
        System.out.println("Press 1 to add a car!");
        System.out.println("Press 2 to add a motorcycle!");
        System.out.println("Press 3 to add a bicycle!");

        String option = inScanner.nextLine();
        String color, brand;

        System.out.print("Enter color of the vehicle: ");
        color = inScanner.nextLine();

        System.out.print("Enter brand of the vehicle: ");
        brand = inScanner.nextLine();

        switch (option) {
            case "1":
                this.vehiclesController.addVehicle(new Car(color, brand));
                break;

            case "2":
                this.vehiclesController.addVehicle(new Motorcycle(color, brand));
                break;

            case "3":
                this.vehiclesController.addVehicle(new Bicycle(color, brand));
                break;

            default:
                System.out.println("Invalid type of vehicle! Bye!");
        }
    }

    private void removeVehicleMenu() {
        System.out.println("Press 1 to remove a car!");
        System.out.println("Press 2 to remove a motorcycle!");
        System.out.println("Press 3 to remove a bicycle!");

        String option = inScanner.nextLine();
        String color, brand;

        System.out.print("Enter color of the vehicle: ");
        color = inScanner.nextLine();

        System.out.print("Enter brand of the vehicle: ");
        brand = inScanner.nextLine();

        switch (option) {
            case "1":
                this.vehiclesController.removeVehicle(new Car(color, brand));
                break;

            case "2":
                this.vehiclesController.removeVehicle(new Motorcycle(color, brand));
                break;

            case "3":
                this.vehiclesController.removeVehicle(new Bicycle(color, brand));
                break;

            default:
                System.out.println("Invalid type of vehicle! Bye!");
        }
    }

    public void mainMenu() {
        String option;

        while (true) {
            printMenu();

            option = inScanner.nextLine();

            try {
                switch (option) {
                    case "0":
                        return;

                    case "1":
                        addVehicleMenu();
                        System.out.println("Vehicle added successfully!");
                        break;

                    case "2":
                        removeVehicleMenu();
                        System.out.println("Vehicle successfully removed!");

                        break;

                    case "3":
                        if (this.vehiclesController.getAll().isEmpty()) {
                            System.out.println("There are no vehicles!");
                            break;
                        }

                        System.out.println("Vehicles are:");
                        for (Vehicle currentVehicle : this.vehiclesController.getAll())
                            System.out.println(currentVehicle);

                        break;

                    case "4":
                        if (this.vehiclesController.filter().isEmpty()) {
                            System.out.println("There are no vehicles!");
                            break;
                        }

                        System.out.println("Filtered vehicles are:");

                        for (Vehicle currentVehicle : this.vehiclesController.filter())
                            System.out.println(currentVehicle);

                        break;

                    default:
                        System.out.println("Please enter a valid option!");
                }
            } catch (RepositoryException re) {
                System.out.println(re.getMessage());
            }

        }
    }
}
