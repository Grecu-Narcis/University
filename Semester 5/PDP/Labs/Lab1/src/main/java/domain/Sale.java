package domain;


import lombok.AllArgsConstructor;
import lombok.Getter;

import lombok.Setter;
import lombok.ToString;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Random;

@Getter
@Setter
@AllArgsConstructor
@ToString
public class Sale {
    private List<Pair<Integer, Integer>> soldItems; // list of id for product and quantity taken

    public Sale() {
        this.soldItems = new ArrayList<>();
    }

    public void addSoldItem(Pair<Integer, Integer> soldItem) {
        this.soldItems.add(soldItem);
    }

    public static Sale generateSale(Map<Integer, Integer> quantities) {
        Sale generatedSale = new Sale();
        Random random = new Random();

        for (Integer productId : quantities.keySet()) {
            if (random.nextInt(100) < 25 || quantities.get(productId).equals(0))
                continue;

            Integer currentProductAvailability = quantities.get(productId);
            Integer quantity = random.nextInt(1, currentProductAvailability + 1);

            quantities.put(productId, currentProductAvailability - quantity);

            generatedSale.getSoldItems().add(new Pair<>(productId, quantity));
        }

        if (generatedSale.soldItems.isEmpty()) return null;

        return generatedSale;
    }
}
