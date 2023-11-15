package repository;

import exceptions.RepositoryException;
import models.Vehicle;

public interface IRepository
{
    void addVehicle(Vehicle vehicleToAdd) throws RepositoryException;
    void removeVehicle(Vehicle vehicleToRemove);
    int getSize();
    Vehicle[] getAll();
}
