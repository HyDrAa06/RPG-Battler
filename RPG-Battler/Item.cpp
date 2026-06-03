#include "Item.h"

Item::Item(const int xpPrice, const ItemType itemType) : xpPrice(xpPrice), itemType(itemType)
{
}

ItemType Item::getType() const
{
    return itemType;
}

int Item::getPrice() const
{
    return xpPrice;
}
