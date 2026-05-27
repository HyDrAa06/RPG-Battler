#include "Item.h"

Item::Item(const std::string name, const int xpPrice, const ItemType itemType) : 
    name(name), xpPrice(xpPrice), itemType(itemType)
{
}

std::string Item::getName() const
{
    return name;
}

int Item::getPrice() const
{
    return xpPrice;
}

ItemType Item::getType(Character* target) const
{
    return itemType;
}
