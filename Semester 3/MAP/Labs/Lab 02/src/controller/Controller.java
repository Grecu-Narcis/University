package controller;

import exceptions.RepositoryException;
import models.Vehicle;
import repository.IRepository;

import java.util.ArrayList;
import java.util.List;

public class Controller {
    private IRepository vehiclesRepository;

    public Controller(IRepository repo)
    {
        vehiclesRepository = repo;
    }

    public void addVehicle(Vehicle vehicleToAdd) throws RepositoryException
    {
        vehiclesRepository.addVehicle(vehicleToAdd);
    }

    public void removeVehicle(Vehicle vehicleToRemove)
    {
        vehiclesRepository.removeVehicle(vehicleToRemove);
    }

    public ArrayList<Vehicle> filter()
    {
        ArrayList<Vehicle> filteredVehicles = new ArrayList<Vehicle>();

        for (Vehicle vehicle : vehiclesRepository.getAll())
        {
            if (vehicle != null && vehicle.getColor().equals("red"))
                filteredVehicles.add(vehicle);
        }

        return filteredVehicles;
    }

    public ArrayList<Vehicle> getAll()
    {
        ArrayList<Vehicle> allVehicles = new ArrayList<Vehicle>();

        for (Vehicle vehicle : vehiclesRepository.getAll())
        {
            if (vehicle != null)
                allVehicles.add(vehicle);
        }

        return allVehicles;
    }
}
