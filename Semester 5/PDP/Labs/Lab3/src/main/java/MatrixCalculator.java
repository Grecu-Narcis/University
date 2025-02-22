import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MatrixCalculator {
    private final int[][] matrix1, matrix2;
    private int[][] resultMatrix;

    public MatrixCalculator(int[][] matrix1, int[][] matrix2) {
        this.matrix1 = matrix1;
        this.matrix2 = matrix2;

        this.reset();
    }

    public MatrixCalculator(int n, int m, int k) {
        this.matrix1 = this.generateMatrix(n, m);
        this.matrix2 = this.generateMatrix(m, k);

        this.reset();
    }

    public int[][] generateMatrix(int n, int m) {
        Random random = new Random();
        int[][] matrix = new int[n][m];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                matrix[i][j] = random.nextInt(1, 11);

        return matrix;
    }

    public void reset() {
        int n = matrix1.length, m = matrix2[0].length;

        resultMatrix = new int[n][m];
    }

    public int computeElement(int row, int column) {
        int result = 0;

        for (int i = 0; i < matrix2.length; i++) {
            result += matrix1[row][i] * matrix2[i][column];
        }

        return result;
    }

    public void computeTask(List<Pair> elements) {
        for (var element : elements) {
            int row = element.getFirst(), column = element.getSecond();
            this.resultMatrix[row][column] = computeElement(row, column);
        }
    }

    public List<List<Pair>> distributeWorkCase1(int numberOfWorkers) {
        List<List<Pair>> indexes = new ArrayList<>();

        int n = resultMatrix.length, m = resultMatrix[0].length;
        int numberOfElementsPerWorker = n * m / numberOfWorkers;

        List<Pair> workerIndexes = new ArrayList<>();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                workerIndexes.add(new Pair(i, j));

                if (workerIndexes.size() == numberOfElementsPerWorker) {
                    indexes.add(List.copyOf(workerIndexes));
                    workerIndexes.clear();
                }
            }

        if (!workerIndexes.isEmpty())
            indexes.add(workerIndexes);

        return indexes;
    }

    public List<List<Pair>> distributeWorkCase2(int numberOfWorkers) {
        List<List<Pair>> indexes = new ArrayList<>();

        int n = resultMatrix.length, m = resultMatrix[0].length;
        int numberOfElementsPerWorker = n * m / numberOfWorkers;

        List<Pair> workerIndexes = new ArrayList<>();

        for (int j = 0; j < m; j++)
            for (int i = 0; i < n; i++) {
                workerIndexes.add(new Pair(i, j));

                if (workerIndexes.size() == numberOfElementsPerWorker) {
                    indexes.add(List.copyOf(workerIndexes));
                    workerIndexes.clear();
                }
            }

        if (!workerIndexes.isEmpty())
            indexes.add(workerIndexes);

        return indexes;
    }

    public List<List<Pair>> distributeWorkCase3(int numberOfWorkers) {
        List<List<Pair>> indexes = new ArrayList<>();

        for (int i = 0; i < numberOfWorkers; i++)
            indexes.add(new ArrayList<>());

        int n = resultMatrix.length, m = resultMatrix[0].length;

        for (int i = 0; i < n * m; i++) {
            int row = i / n;
            int column = i % m;

            indexes.get(i % numberOfWorkers).add(new Pair(row, column));
        }

        return indexes;
    }

    public void executeWorkWithoutThreadPool(List<List<Pair>> indexes) {
        List<Thread> workers = new ArrayList<>();

        for (var workerIndexes : indexes) {
            Thread worker = new Thread(() -> {
                computeTask(workerIndexes);
            });

            workers.add(worker);
            worker.start();
        }

        for (var worker : workers) {
            try {
                worker.join();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public void executeWorkWithThreadPool(List<List<Pair>> indexes, int threadPoolSize) {
        try (ExecutorService executorService = Executors.newFixedThreadPool(threadPoolSize)) {
            for (var workerIndexes : indexes) {
                executorService.submit(() ->
                    computeTask(workerIndexes)
                );
            }
        }
    }

    public void printResult() {
        System.out.println("Result is:");

        for (int i = 0; i < resultMatrix.length; i++) {
            for (int j = 0; j < resultMatrix[0].length; j++)
                System.out.print(resultMatrix[i][j] + " ");

            System.out.println();
        }

        System.out.println();
    }
}
