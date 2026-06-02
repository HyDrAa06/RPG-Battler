#pragma once
#include <iostream>
#include "Character.h"

enum class ItemType
{
	HEALING_POTION,
	BLADE,
	MIRROR,
	BEAM,
	SHIELD
};


class Item
{
protected:
	int xpPrice;	
	ItemType itemType;

public:
	Item(const int xpPrice, const ItemType itemType);
	virtual ~Item() = default;

	virtual void use(Character* target) = 0;

	ItemType getType(Item* target) const;
	int getPrice() const;
	virtual std::unique_ptr<Item> clone() const = 0;

};

