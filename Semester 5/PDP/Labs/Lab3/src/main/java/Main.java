public class Main {
    public static void main(String[] args) {
        MatrixCalculator matrixCalculator = new MatrixCalculator(100, 120, 42);

        var indexes = matrixCalculator.distributeWorkCase1(32);

        long startTime = System.currentTimeMillis();
        matrixCalculator.executeWorkWithoutThreadPool(indexes);
        long endTime = System.currentTimeMillis();

        System.out.println("Time without thread pool: " + (endTime - startTime) + " ms.");

        matrixCalculator.reset();

        startTime = System.currentTimeMillis();
        matrixCalculator.executeWorkWithThreadPool(indexes, 32);
        endTime = System.currentTimeMillis();

        System.out.println("Time with thread pool: " + (endTime - startTime) + " ms.");
    }
}
