package ubb.models.adts;

import ubb.exceptions.ListException;

import java.util.ArrayList;
import java.util.List;

// TODO: add custom exceptions!

public class MyList<T> implements MyIList<T> {
    private final List<T> itemsList;

    public MyList()
    {
        itemsList = new ArrayList<>();
    }

    @Override
    public void add(T itemToAdd) {
        synchronized (itemsList) {
            itemsList.add(itemToAdd);
        }
    }

    @Override
    public void remove(int position) throws ListException {
        synchronized (itemsList) {
            if (position >= itemsList.size())
                throw new ListException("Index out of bound!");

            itemsList.remove(position);
        }
    }

    @Override
    public boolean remove(T itemToRemove) {
        synchronized (itemsList) {
            return itemsList.remove(itemToRemove);
        }
    }

    @Override
    public T get(int position) throws ListException {
        synchronized (itemsList) {
            if (position >= itemsList.size())
                throw new ListException("Index out of bound!");

            return itemsList.get(position);
        }
    }

    @Override
    public List<T> getOutput() {
        synchronized (itemsList) {
            return this.itemsList;
        }
    }

    @Override
    public void set(int position, T newValue) throws ListException {
        synchronized (itemsList) {
            if (position >= itemsList.size())
                throw new ListException("Index out of bound!");

            itemsList.set(position, newValue);
        }
    }

    @Override
    public String toString() {
        return "MyList{" +
                "itemsList=" + itemsList +
                '}';
    }
}
