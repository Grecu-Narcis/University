package repository;

import domain.Product;
import lombok.Getter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

public class ProductRepository {
    private final List<Product> availableProducts;
    @Getter private final List<ReentrantLock> mutexes;

    public ProductRepository() {
        this.availableProducts = new ArrayList<>();
        this.mutexes = new ArrayList<>();

        for (int i = 0; i < 10; i++) {
            this.availableProducts.add(Product.generateProduct(i));
            this.mutexes.add(new ReentrantLock());
        }
    }

    public ProductRepository(int productsCount) {
        this.availableProducts = new ArrayList<>();
        this.mutexes = new ArrayList<>();

        for (int i = 0; i < productsCount; i++) {
            this.availableProducts.add(Product.generateProduct(i));
            this.mutexes.add(new ReentrantLock());
        }
    }

    public List<Product> getProducts() {
        return this.availableProducts;
    }

    public ReentrantLock getMutexForProduct(int productId) {
        return this.mutexes.get(productId);
    }

    public Map<Integer, Integer> getQuantitiesByProduct() {
        Map<Integer, Integer> quantities = new HashMap<>();

        for (Product currentProduct : availableProducts)
            quantities.put(currentProduct.getId(), currentProduct.getQuantity());

        return quantities;
    }

    public Integer getProductPrice(Integer productId) {
        return this.availableProducts.get(productId).getPrice();
    }
}
