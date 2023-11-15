package repository;

import exceptions.RepositoryException;
import models.Vehicle;

public class InMemoryRepository implements IRepository
{
    private Vehicle[] vehicles;
    private int size, capacity;

    public InMemoryRepository()
    {
        vehicles = new Vehicle[10];
        size = 0;
        capacity = 10;
    }

    @Override
    public void addVehicle(Vehicle vehicleToAdd) throws RepositoryException
    {
        if (size == capacity)
            throw new RepositoryException("Repository is full!");

        vehicles[size++] = vehicleToAdd;
    }

    @Override
    public void removeVehicle(Vehicle vehicleToRemove)
    {
        for (int i = 0; i < this.size; i++)
            if (vehicles[i].equals(vehicleToRemove))
            {
                for (int j = i; j < this.size - 1; j++)
                    vehicles[j] = vehicles[j + 1];

                vehicles[size - 1] = null;
                size--;
            }
    }

    @Override
    public int getSize()
    {
        return this.size;
    }

    @Override
    public Vehicle[] getAll()
    {
        return this.vehicles;
    }
}
