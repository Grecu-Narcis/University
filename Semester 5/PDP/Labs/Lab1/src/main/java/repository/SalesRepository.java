package repository;

import domain.Sale;

import java.util.ArrayList;
import java.util.List;

public class SalesRepository {
    private final List<Sale> sales;

    public SalesRepository() {
        this.sales = new ArrayList<>();
    }

    public void addSale(Sale saleToAdd) {
        sales.add(saleToAdd);
    }

    public List<Sale> getSales() {
        return this.sales;
    }
}
