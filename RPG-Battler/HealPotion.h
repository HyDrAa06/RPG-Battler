#pragma once
#include "Item.h"
class HealPotion : public Item
{
public:
	HealPotion(const std::string name);
	void use(Character* target) override;
};

