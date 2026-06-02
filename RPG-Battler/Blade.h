#pragma once
#include "Item.h"

class Blade : public Item
{
public:
	Blade();
	void use(Character* target) override;
	std::unique_ptr<Item> clone() const override;

};

