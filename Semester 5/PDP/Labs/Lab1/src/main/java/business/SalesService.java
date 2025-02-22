package business;

import domain.Bill;
import domain.Pair;
import domain.Product;
import domain.Sale;
import repository.BillRepository;
import repository.ProductRepository;
import utils.Logger;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

public class SalesService {
    private final ProductRepository productRepository;
    private final BillRepository billRepository;
    private Integer totalAmount;
    private final ReentrantLock totalAmountMutex;
    private final Random random;
    private final Logger logger;

    public SalesService(ProductRepository productRepository, BillRepository billRepository) {
        this.productRepository = productRepository;
        this.billRepository = billRepository;

        this.totalAmount = 0;
        this.totalAmountMutex = new ReentrantLock();
        random = new Random();
        logger = Logger.getLogger();
    }

    private Pair<Integer, Integer> attemptSellProduct(Product productToSell) {
        if (random.nextInt() < 25) // 75% chance of getting current product
            return null;

        if (productToSell.getQuantity().equals(0))
            return null;

        Integer takenQuantity = random.nextInt(1, productToSell.getQuantity() + 1);
        productToSell.setQuantity(productToSell.getQuantity() - takenQuantity);

        return new Pair<>(productToSell.getId(), takenQuantity);
    }

    private void generateSale() {
        Sale generatedSale = new Sale();
        Bill bill = new Bill();
        this.billRepository.addBill(bill);

        for (Product currentProduct : productRepository.getProducts()) {
            ReentrantLock currentProductLock = this.productRepository.getMutexForProduct(currentProduct.getId());
            currentProductLock.lock();
            Pair<Integer, Integer> productSold = this.attemptSellProduct(currentProduct);

            if (productSold == null) {
                currentProductLock.unlock();
                continue;
            }

            generatedSale.addSoldItem(productSold);
            bill.addProductSale(productSold, this.productRepository.getProductPrice(productSold.getFirst()));

            this.totalAmountMutex.lock();
            this.totalAmount += this.productRepository.getProductPrice(productSold.getFirst()) * productSold.getSecond();
            this.totalAmountMutex.unlock();

            currentProductLock.unlock();
        }

    }

    public void executeSales(int numberOfWorkers) {
        List<Thread> workers = new ArrayList<>();

        for (int i = 0; i < numberOfWorkers; i++) {
            Thread thread = new Thread(this::generateSale);
            workers.add(thread);

            thread.start();
        }

        for (Thread worker : workers) {
            try {
                worker.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        Thread checker = new Thread(() -> {
            int checks = 5;

            while (checks > 0) {
                try {
//                    Thread.sleep(100);
                    checks--;

                    this.runChecks();
                } catch (Exception e) {
                    Thread.currentThread().interrupt();
                }
            }
        });

        checker.start();

        try {
            checker.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println(this.totalAmount);
    }

    public void executeSales(int numberOfWorkers, int totalSales) {
        List<Thread> workers = new ArrayList<>();
        int salesPerWorker = totalSales / numberOfWorkers;
        int remainingSales = totalSales % numberOfWorkers; // To handle extra sales

        for (int i = 0; i < numberOfWorkers; i++) {
            int salesToExecute = i < remainingSales ? salesPerWorker + 1 : salesPerWorker;

            Thread thread = new Thread(() -> executeSaleBatch(salesToExecute));
            workers.add(thread);
            thread.start();
        }

        for (Thread worker : workers) {
            try {
                worker.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        Thread checker = new Thread(() -> {
            int checks = 5;

            while (checks > 0) {
                try {
//                    Thread.sleep(100);
                    checks--;

                    this.runChecks();
                } catch (Exception e) {
                    Thread.currentThread().interrupt();
                }
            }
        });

        checker.start();

        try {
            checker.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println(this.totalAmount);
    }

    private void executeSaleBatch(int salesToExecute) {
        for (int i = 0; i < salesToExecute; i++) {
            generateSale();
        }
    }

    public void checkQuantityConsistency() throws Exception {
        for (Product product : this.productRepository.getProducts()) {
            Integer soldProducts = this.billRepository.getBills().stream()
                .map(Bill::getSoldItems)
                .map(soldItems ->
                    soldItems.stream()
                        .filter(item -> item.getFirst().equals(product.getId()))
                        .map(Pair::getSecond)
                        .reduce(0, Integer::sum))
                .reduce(0, Integer::sum);

            if (!product.getInitialQuantity().equals(soldProducts + product.getQuantity()))
                throw new Exception(String.format("Product quantity not consistent! Error found at product: %d", product.getId()));
        }

        logger.logSuccess("Check done! State is consistent!");
    }

    public void checkAmountConsistency() throws Exception {
        Integer billsAmount = this.billRepository.getBills()
            .stream()
            .map(Bill::getTotalPrice)
            .reduce(0, Integer::sum);

        if (!billsAmount.equals(this.totalAmount))
            throw new Exception("Total amount not consistent!");

        logger.logSuccess("Check done! Total amount is consistent!");
    }

    public void runChecks() {
//        this.productRepository.getMutexes().forEach(ReentrantLock::lock);

        try {
            this.checkAmountConsistency();
            this.checkQuantityConsistency();
        } catch (Exception e) {
            logger.logError(e.getMessage());

            System.out.println("--------Bills----------");
            this.billRepository.getBills().forEach(System.out::println);

            System.out.println("--------Product---------");
            this.productRepository.getProducts().forEach(System.out::println);
        }

//        this.productRepository.getMutexes().forEach(ReentrantLock::unlock);
    }
}
