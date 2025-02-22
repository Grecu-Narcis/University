package domain;

import lombok.*;

import java.util.Random;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
@EqualsAndHashCode
public class Product {
    private Integer id;
    private Integer price;
    private Integer quantity;
    private Integer initialQuantity;

    public static Product generateProduct(int index) {
        Random random = new Random();
        Integer price = random.nextInt(10) + 1;
        Integer quantity = random.nextInt(1000, 2001);

        return new Product(index, price, quantity, quantity);
    }
}
