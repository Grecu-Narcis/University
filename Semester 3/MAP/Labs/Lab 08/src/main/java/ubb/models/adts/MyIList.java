package ubb.models.adts;

import ubb.exceptions.ListException;

import java.util.List;

public interface MyIList<T> {
    void add(T itemToAdd);
    void remove(int position) throws ListException;
    boolean remove(T itemToRemove);
    T get(int position) throws ListException;
    void set(int position, T newValue) throws ListException;
    List<T> getOutput();
}
