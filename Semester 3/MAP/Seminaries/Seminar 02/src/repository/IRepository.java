package repository;

import models.Item;
public interface IRepository {
    void addItem(Item itemToAdd);
    // void removeItem(Item itemToRemove);
    Item[] getAll();
    int getSize();
}
