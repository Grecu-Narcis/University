package models.utils;

import java.util.HashMap;
import java.util.Map;

public class MyDictionary<TKey, TValue> implements MyIDictionary<TKey, TValue> {
    private final Map<TKey, TValue> dictionary;

    public MyDictionary()
    {
        dictionary = new HashMap<TKey, TValue>();
    }

    @Override
    public TValue get(TKey keyToSearch) {
        return dictionary.get(keyToSearch);
    }

    @Override
    public void put(TKey keyToAdd, TValue valueToAdd) {
        dictionary.put(keyToAdd, valueToAdd);
    }

    @Override
    public void update(TKey keyToUpdate, TValue newValue) {
        dictionary.put(keyToUpdate, newValue);
    }

    @Override
    public boolean isDefined(TKey keyToSearch) {
        return dictionary.containsKey(keyToSearch);
    }

    @Override
    public String toString() {
        return "MyDictionary{" +
                "dictionary=" + dictionary +
                '}';
    }
}
