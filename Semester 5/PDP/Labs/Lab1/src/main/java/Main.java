import business.SalesService;
import repository.BillRepository;
import repository.ProductRepository;

import java.util.List;


public class Main {
    public static void main(String[] args) {
        ProductRepository productRepository = new ProductRepository(10);
        BillRepository billRepository = new BillRepository();

        SalesService salesService = new SalesService(productRepository, billRepository);

        List<Integer> threadsNumber = List.of(1, 2, 4, 8, 16);
        List<Integer> totalSalesValues = List.of(10, 100, 1000, 10000, 100000);

        for (var threads : threadsNumber)
            for (var totalSales : totalSalesValues) {
                computeExecutionTime(() -> {
                    salesService.executeSales(threads, totalSales);
                    System.out.printf("Time for %d threads and %d sales: ", threads, totalSales);
                });
            }

        salesService.executeSales(5);
    }

    // 2026 ms -> 1 thread
    // 4609 ms -> 2 thread
    private static void computeExecutionTime(Runnable task) {
        long startTime = System.currentTimeMillis();

        task.run();

        long endTime = System.currentTimeMillis();
        long executionTime = endTime - startTime;

        System.out.println(executionTime + " ms");
    }
}
