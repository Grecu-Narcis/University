import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    public static void main(String[] args) {
        int vectorSize = 10;
        List<Integer> vector1, vector2;
        vector1 = generateRandomVector(vectorSize);
        vector2 = generateRandomVector(vectorSize);

        System.out.println("First vector is: " + vector1);
        System.out.println("Second vector is: " + vector2);

        LinkedList<Integer> intermediateResults = new LinkedList<>();

        ReentrantLock lock = new ReentrantLock();
        Object areAvailableElements = new Object();

        Consumer consumer = new Consumer(intermediateResults, vectorSize, areAvailableElements, lock);
        Producer producer = new Producer(vector1, vector2, intermediateResults, areAvailableElements, lock);

        Thread consumerThread = new Thread(consumer);
        Thread producerThread = new Thread(producer);

        consumerThread.start();
        producerThread.start();


        try {
            consumerThread.join();
            producerThread.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        int expectedScalarProduct = computeScalarProduct(vector1, vector2);
        System.out.println("Expected scalar product is: " + expectedScalarProduct);
    }

    public static List<Integer> generateRandomVector(int size) {
        Random random = new Random();

        List<Integer> generatedVector = new ArrayList<>();

        for (int i = 0; i < size; i++)
            generatedVector.add(random.nextInt(-10, 11));

        return generatedVector;
    }

    public static Integer computeScalarProduct(List<Integer> vector1, List<Integer> vector2) {
        int result = 0;

        for (int i = 0; i < vector1.size(); i++)
            result += vector1.get(i) * vector2.get(i);

        return result;
    }
}
