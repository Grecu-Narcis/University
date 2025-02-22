package domain;

import lombok.*;

import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@ToString
@AllArgsConstructor
public class Bill {
    private List<Pair<Integer, Integer>> soldItems;
    private Integer totalPrice;

    public Bill() {
        this.soldItems = new ArrayList<>();
        this.totalPrice = 0;
    }

    public void addProductSale(Pair<Integer, Integer> product, int productPrice) {
        this.soldItems.add(product);
        this.totalPrice += productPrice * product.getSecond();
    }
}
