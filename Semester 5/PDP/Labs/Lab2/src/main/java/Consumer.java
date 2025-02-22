import java.util.Queue;
import java.util.concurrent.locks.ReentrantLock;

public class Consumer implements Runnable {
    private final Queue<Integer> intermediateResults;
    private final Object condition;
    private final ReentrantLock lock;
    private Integer finalSum = 0;
    private final Integer vectorSize;

    public Consumer(Queue<Integer> intermediateResults, Integer vectorSize, Object condition, ReentrantLock lock) {
        this.intermediateResults = intermediateResults;
        this.condition = condition;
        this.lock = lock;

        this.vectorSize = vectorSize;
    }

    @Override
    public void run() {
        int index = 0;

        try {
            while (index < this.vectorSize) {
                synchronized (condition) {
                    while (intermediateResults.isEmpty())
                        this.condition.wait();
                }

                while (!intermediateResults.isEmpty()) {
                    lock.lock();
                    Integer currentResult = intermediateResults.remove();
                    lock.unlock();
                    System.out.println("Consumed values at position: " + index);

                    index++;

                    this.finalSum += currentResult;
                }
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("Scalar product from producer-consumer is: " + this.finalSum);
    }
}
