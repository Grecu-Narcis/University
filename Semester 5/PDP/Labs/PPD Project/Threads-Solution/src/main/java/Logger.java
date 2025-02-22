import java.util.concurrent.locks.ReentrantLock;

public class Logger {
    private static final ReentrantLock logLock = new ReentrantLock();

    public static void log(String message) {
        logLock.lock();

        System.out.println(message);

        logLock.unlock();
    }
}
