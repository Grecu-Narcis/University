import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class Polynomial {
    // a0 + a1 * x + a2 * x^2 +...
    private List<Integer> coefficients;
    private int degree;
    ExecutorService executorService = new ForkJoinPool(100);

    public Polynomial(int degree) {
        this.degree = degree;
        this.coefficients = new ArrayList<>();

        for (int i = 0; i <= this.degree; i++)
            this.coefficients.add(0);
    }

    public Polynomial(List<Integer> coefficients) {
        if (coefficients.isEmpty()) {
            this.degree = 0;
            this.coefficients = List.of(0);
            return;
        }

        this.degree = coefficients.size() - 1;
        this.coefficients = coefficients;
    }

    public Polynomial multiply(Polynomial second) {
        Polynomial result = new Polynomial(this.degree + second.degree);

        for (int i = 0; i <= this.degree; i++)
            for (int j = 0; j <= second.degree; j++) {
                int prevValue = result.coefficients.get(i + j);
                result.coefficients.set(i + j, prevValue + this.coefficients.get(i) * second.coefficients.get(j));
            }

        return result;
    }

    public Polynomial multiplyWithThreads(Polynomial second) {
        try (ExecutorService executorService = Executors.newFixedThreadPool(4)) {
            Polynomial result = new Polynomial(this.degree + second.degree);

            List<Callable<Integer>> tasks = new ArrayList<>();

            for (int i = 0; i <= this.degree; i++) {
                int finalI = i;
                tasks.add(() -> {
                    for (int j = 0; j <= second.degree; j++) {
                        synchronized (result) {
                            int prevValue = result.coefficients.get(finalI + j);
                            result.coefficients.set(finalI + j, prevValue + this.coefficients.get(finalI) * second.coefficients.get(j));
                        }
                    }

                    return 1;
                });
            }

            executorService.invokeAll(tasks);

            return result;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public Polynomial multiplyKaratsuba(Polynomial second) {
        return this.recursiveKaratsuba(second);
    }

    public Polynomial multiplyKaratsubaWithThreads(Polynomial second) {
        return this.threadedKaratsuba(second);
    }

    public Polynomial threadedKaratsuba(Polynomial second) {
        try {
            int n = Math.max(this.coefficients.size(), second.coefficients.size());

            if (n == 1) {
                return new Polynomial(List.of(this.coefficients.getFirst() * second.coefficients.getFirst()));
            }

            int half = (n + 1) / 2;

            Polynomial A0 = this.getLowerHalf(half);
            Polynomial A1 = this.getUpperHalf(half);

            Polynomial B0 = second.getLowerHalf(half);
            Polynomial B1 = second.getUpperHalf(half);

            Future<Polynomial> u_future = executorService.submit(() -> A0.multiplyKaratsuba(B0));
            Future<Polynomial> v_future = executorService.submit(() -> A0.multiplyKaratsuba(B1));
            Future<Polynomial> w_future = executorService.submit(() -> A1.multiplyKaratsuba(B0));
            Future<Polynomial> z_future = executorService.submit(() -> A1.multiplyKaratsuba(B1));

            Polynomial U = u_future.get();
            Polynomial V = v_future.get();
            Polynomial W = w_future.get();
            Polynomial Z = z_future.get();

            Polynomial V_and_W = V.add(W).shift(half);

            return U.add(V_and_W).add(Z.shift(2 * half));
        }
        catch (InterruptedException | ExecutionException e) {
            System.out.println(e.getMessage());
        }

        return new Polynomial(0);
    }

    public Polynomial recursiveKaratsuba(Polynomial second) {
        int n = Math.max(this.coefficients.size(), second.coefficients.size());

        if (n == 1) {
            return new Polynomial(List.of(this.coefficients.getFirst() * second.coefficients.getFirst()));
        }

        int half = (n + 1) / 2;

        Polynomial A0 = this.getLowerHalf(half);
        Polynomial A1 = this.getUpperHalf(half);

        Polynomial B0 = second.getLowerHalf(half);
        Polynomial B1 = second.getUpperHalf(half);

        Polynomial U = A0.multiplyKaratsuba(B0);
        Polynomial V = A0.multiplyKaratsuba(B1);
        Polynomial W = A1.multiplyKaratsuba(B0);
        Polynomial Z = A1.multiplyKaratsuba(B1);

        Polynomial V_and_W = V.add(W).shift(half);

        return U.add(V_and_W).add(Z.shift(2 * half));
    }

    private Polynomial getLowerHalf(int half) {
        return new Polynomial(this.coefficients.subList(0, half));
    }

    private Polynomial getUpperHalf(int half) {

        return new Polynomial(this.coefficients.subList(half, this.coefficients.size()));
    }

    public Polynomial add(Polynomial second) {
        Polynomial result = new Polynomial(Math.max(this.degree, second.degree));

        for (int i = 0; i <= this.degree; i++)
            result.coefficients.set(i, result.coefficients.get(i) + this.coefficients.get(i));

        for (int i = 0; i <= second.degree; i++)
            result.coefficients.set(i, result.coefficients.get(i) + second.coefficients.get(i));

        return result;
    }

    public Polynomial shift(int positions) {
        List<Integer> newCoefficients = new ArrayList<>(this.coefficients);
        for (int i = 0; i < positions; i++) {
            newCoefficients.addFirst(0);
        }
        return new Polynomial(newCoefficients);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = this.degree; i >= 0; i--) {
            if (this.coefficients.get(i) == 0)
                continue;

            sb.append(this.coefficients.get(i));
            if (i > 0) {
                sb.append("x^").append(i);
            }
            if (i > 0) {
                sb.append(" + ");
            }

        }
        return sb.toString();
    }
}
