package models.utils;

import exceptions.ListException;

public interface MyIList<T> {
    void add(T itemToAdd);
    void remove(int position) throws ListException;
    boolean remove(T itemToRemove);
    T get(int position) throws ListException;
    void set(int position, T newValue) throws ListException;
}
