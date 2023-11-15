package repository;

import models.Item;

public class InMemoryRepository implements IRepository{
    private Item[] items;
    private int size, capacity;

    public InMemoryRepository(int capacity)
    {
        items = new Item[capacity];
        this.capacity = capacity;
        this.size = 0;
    }

    public InMemoryRepository()
    {
        this(100);
    }

    @Override
    public void addItem(Item itemToAdd)
    {
        if (size >= capacity)
            throw new RuntimeException("Repository is full!");

        items[size++] = itemToAdd;
    }

    @Override
    public Item[] getAll()
    {
        return this.items;
    }

    @Override
    public int getSize() {
        return size;
    }
}
