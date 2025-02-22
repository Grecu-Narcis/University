package repository;

import domain.Bill;

import java.util.ArrayList;
import java.util.List;

public class BillRepository {
    private final List<Bill> bills;

    public BillRepository() {
        this.bills = new ArrayList<>();
    }

    public void addBill(Bill billToAdd) {
        synchronized (this.bills) {
            this.bills.add(billToAdd);
        }
    }

    public List<Bill> getBills() {
        return this.bills;
    }
}
