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
	std::string name;

public:
	Item(const std::string name, const int xpPrice, const ItemType itemType);
	virtual ~Item() = default;

	virtual void use(Character* target) = 0;

	ItemType getType(Item* target) const;
};

