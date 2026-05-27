#pragma once
#include <iostream>
#include "Character.h"

enum class ItemType
{
	HEALING_POTION,
	BLADE,
	MIRROR,
	RAY,
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

	virtual void use() = 0;

	std::string getName() const;
	int getPrice() const;
	ItemType getType(Character* target) const;
};

