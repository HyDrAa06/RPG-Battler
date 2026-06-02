#pragma once
#include "Item.h"
class HealPotion : public Item
{
public:
	HealPotion();
	void use(Character* target) override;
	std::unique_ptr<Item> clone() const override;

};

