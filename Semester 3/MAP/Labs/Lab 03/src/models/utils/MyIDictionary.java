package models.utils;

public interface MyIDictionary<TKey, TValue> {
    TValue get(TKey keyToSearch);
    void put(TKey keyToAdd, TValue valueToAdd);
    void update(TKey keyToUpdate, TValue newValue);
    boolean isDefined(TKey keyToSearch);
}
