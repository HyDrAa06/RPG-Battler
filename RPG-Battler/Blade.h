#pragma once
#include "Item.h"

class Blade : public Item
{
public:
	Blade(const std::string name);
	void use(Character* target) override;
};

