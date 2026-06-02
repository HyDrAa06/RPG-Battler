#include "Shield.h"
#include "Character.h"
#include <iostream>
#include "CharacterStats.h"

Shield::Shield() : Item( item_stats::SHIELD_XP, ItemType::SHIELD) 
{
}

void Shield::use(Character* target)
{
	std::cout << "You have used a shield: "  << std::endl;
	std::cout << "All dmg is blocked and your turn is not wasted!";
}

std::unique_ptr<Item> Shield::clone() const
{
	return std::make_unique<Item>(*this);
}