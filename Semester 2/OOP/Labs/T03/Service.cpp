#include "Service.h"

#include <algorithm>
#include <iterator>

Service::Service(Repository& itemsRepository) : itemsRepository{ itemsRepository }
{
}

vector<Item> Service::getAll()
{
	return itemsRepository.getAll();
}

vector<Item> Service::getAllSortedByCategoryAndName()
{
	vector<Item> allItems = this->getAll();

	std::sort(allItems.begin(), allItems.end(),
		[](Item firstItem, Item secondItem)
		{
			if (firstItem.getCategory() == secondItem.getCategory())
				return firstItem.getName() < secondItem.getName();

			return firstItem.getCategory() < secondItem.getCategory();
		});

	return allItems;
}

vector<Item> Service::getAllItemsWithGivenCategoryOrName(string requiredString)
{
	vector<Item> allItems = this->getAll();
	vector<Item> itemsRequired;

	std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(itemsRequired),
		[requiredString](Item currentItem)
		{
			return currentItem.getCategory().find(requiredString) != std::string::npos ||
				currentItem.getName().find(requiredString) != std::string::npos;
		});

	return itemsRequired;
}

vector<Item> Service::getAllItemsFromCategory(string requiredCategory)
{
	vector<Item> allItems = this->getAll();
	vector<Item> itemsRequired;

	std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(itemsRequired),
		[requiredCategory](Item currentItem)
		{
			return currentItem.getCategory() == requiredCategory;
		});

	std::sort(itemsRequired.begin(), itemsRequired.end(),
		[](Item firstItem, Item secondItem)
		{
			return firstItem.getQuantity() >= secondItem.getQuantity();
		});

	return itemsRequired;
}
