package utils;

public class Logger {
    private static Logger logger;

    private Logger() {

    }

    public static Logger getLogger() {
        if (logger == null)
            logger = new Logger();

        return logger;
    }

    public void logError(String message) {
        System.out.println("🛑 " + message);
    }

    public void logSuccess(String message) {
        System.out.println("✅ " + message);
    }
}
