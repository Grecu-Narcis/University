package ubb.models.adts;

import ubb.exceptions.StackException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T> {
    private final Stack<T> stack;

    public MyStack()
    {
        stack = new Stack<>();
    }

    @Override
    public T pop() throws StackException
    {
        if (stack.empty())
            throw new StackException("Stack is empty!");

        return stack.pop();
    }

    @Override
    public boolean isEmpty() {
        return stack.empty();
    }

    @Override
    public void push(T itemToPush)
    {
        stack.push(itemToPush);
    }

    @Override
    public List<T> reverse() {
        ArrayList<T> reversedStack = new ArrayList<>(stack);

        Collections.reverse(reversedStack);

        return reversedStack;
    }

    @Override
    public List<T> getStackAsList() {
        return new ArrayList<>(stack);
    }

    @Override
    public String toString() {
        return "MyStack{" +
                "stack=" + this.reverse() +
                '}';
    }
}
