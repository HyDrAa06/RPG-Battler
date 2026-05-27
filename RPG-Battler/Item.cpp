#include "Item.h"

Item::Item(const std::string name, const int xpPrice, const ItemType itemType) : 
    name(name), xpPrice(xpPrice), itemType(itemType)
{
}

ItemType Item::getType(Item* target) const
{
    return itemType;
}
