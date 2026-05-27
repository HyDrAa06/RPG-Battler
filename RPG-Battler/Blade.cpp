#include "Blade.h"
#include "CharacterStats.h"
#include <cstdlib>

Blade::Blade(const std::string name) : Item(name, item_stats::BLADE_XP, ItemType::BLADE)
{
}

void Blade::use(Character* target)
{
	std::cout << "Used a blade: " << name << std::endl;
	std::cout << "Your next attack will deal 2x dmg!\n";
}
