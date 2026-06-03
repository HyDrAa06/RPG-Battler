#include "Warrior.h"
#include "Character.h"
#include "CharacterStats.h"
#include <cstdlib>

Warrior::Warrior(const std::string name) : Character(name, warrior_stats::MAX_HP, warrior_stats::MIN_DMG, warrior_stats::MAX_DMG)
{
}

int Warrior::calculateDmg()
{
	int dmg = (rand() % (maxDmg - minDmg + 1)) + minDmg;
	return dmg;
}

void Warrior::takeDmg(const int dmg, bool isAbilityBlocked)
{
	if (isAbilityBlocked)
	{
		std::cout << "[MIRROR] Warrior's defense is blocked! He takes full damage: " << dmg << "\n";
		Character::takeDmg(dmg, isAbilityBlocked);
		return;
	}

	int blockAmount = (rand() % 4) + 1;
	int actualDmg = dmg - blockAmount;

	if (actualDmg < 0) actualDmg = 0;

	Character::takeDmg(actualDmg);
}

std::unique_ptr<Character> Warrior::clone() const
{
	return std::make_unique<Warrior>(*this);
}