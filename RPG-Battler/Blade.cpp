#include "Blade.h"
#include "CharacterStats.h"
#include <cstdlib>

Blade::Blade() : Item(item_stats::BLADE_XP, ItemType::BLADE)
{
}

void Blade::use(Character* target)
{
	std::cout << "Used a blade: " << std::endl;
	std::cout << "Your next attack will deal 2x dmg!\n";
}


std::unique_ptr<Item> Blade::clone() const
{
	return std::make_unique<Blade>(*this);
}
