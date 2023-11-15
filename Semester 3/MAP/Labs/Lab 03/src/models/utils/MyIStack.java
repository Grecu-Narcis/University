package models.utils;

import exceptions.StackException;
import exceptions.StatementException;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws StackException;
    void push(T itemToPush);
    boolean isEmpty();

    List<T> reverse();
}
