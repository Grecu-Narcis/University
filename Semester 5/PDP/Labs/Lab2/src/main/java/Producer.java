import java.util.List;
import java.util.Queue;
import java.util.concurrent.locks.ReentrantLock;

public class Producer implements Runnable {
    private final Object condition;
    private final ReentrantLock lock;

    private final List<Integer> vector1, vector2;
    private final Queue<Integer> intermediateResults;

    public Producer(List<Integer> vector1, List<Integer> vector2, Queue<Integer> intermediateResults, Object condition, ReentrantLock lock) {
        this.condition = condition;
        this.lock = lock;

        this.vector1 = vector1;
        this.vector2 = vector2;
        this.intermediateResults = intermediateResults;
    }

    @Override
    public void run() {
        for (int i = 0; i < vector1.size(); i++) {
            Integer currentResult = vector1.get(i) * vector2.get(i);

            lock.lock();
            intermediateResults.add(currentResult);
            lock.unlock();

            System.out.println("Produced value at index: " + i);

            synchronized (condition) {
                condition.notifyAll();
            }
        }
    }
}
