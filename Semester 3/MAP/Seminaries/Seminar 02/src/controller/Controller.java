package controller;

import models.Item;
import repository.IRepository;

import java.util.*;

public class Controller {
    private IRepository itemsRepository;

    public Controller(IRepository repo)
    {
        itemsRepository = repo;
    }

    public void addItem(Item item)
    {
        this.itemsRepository.addItem(item);
    }

    public List<Item> filter(float weight)
    {
        List<Item> filteredItems = new ArrayList<Item>();

//        for (int i = 0; i < itemsRepository.getSize(); i++) {
//            Item currentItem = itemsRepository.getAll()[i];
//
//            if (currentItem.getWeight() > weight)
//                filteredItems.add(currentItem);
//        }

        for (Item currentItem : itemsRepository.getAll())
            if (currentItem.getWeight() > weight)
                filteredItems.add(currentItem);

        return filteredItems;
    }
}
