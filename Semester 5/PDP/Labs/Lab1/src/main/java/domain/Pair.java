package domain;


import lombok.*;

@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class Pair<T, V> {
    private T first;
    private V second;
}
