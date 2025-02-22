import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        List<Integer> coefficients = new ArrayList<>();
        Random random = new Random();

        for (int i = 0; i < 2000; i++)
            coefficients.add(random.nextInt(1, 11));

        Polynomial p1 = new Polynomial(coefficients);
        Polynomial p2 = new Polynomial(coefficients);

        long start = System.currentTimeMillis();
        p1.multiply(p2);

        System.out.println(String.format("Basic multiplication no threads: %d ms", System.currentTimeMillis() - start));

        start = System.currentTimeMillis();
        p1.multiplyWithThreads(p2);
        System.out.println(String.format("Basic multiplication with threads: %d ms", System.currentTimeMillis() - start));

        start = System.currentTimeMillis();
        p1.multiplyKaratsuba(p2);

        System.out.println(String.format("Karatsuba multiplication no threads: %d ms", System.currentTimeMillis() - start));

        start = System.currentTimeMillis();
        p1.multiplyKaratsubaWithThreads(p2);
        System.out.println(String.format("Karatsuba multiplication threaded: %d ms", System.currentTimeMillis() - start));
    }
}
