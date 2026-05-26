#include "Mage.h"
#include "Character.h"
#include "CharacterStats.h"
#include <cstdlib>

Mage::Mage(const std::string name) : Character(name, mage_stats::MAX_HP, mage_stats::MIN_DMG, mage_stats::MAX_DMG)
{
}

int Mage::calculateDmg()
{
	int dmg = (rand() % (maxDmg - minDmg + 1)) + minDmg;

	bool change = changeDmg(dmg);
	if (change == true)
	{
		return mage_stats::MAX_DMG - dmg;
	}

	return dmg;
}

bool Mage::changeDmg(const int dmg) const
{
	int choice = -1;
	std::cout << "Change damage (From " << dmg << " to " << mage_stats::MAX_DMG - dmg << ")?\n";
	std::cout << "YES (1)/ NO (0)";
	std::cin >> choice;

	return choice;
}