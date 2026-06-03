#include "Archer.h"
#include "Character.h"
#include "CharacterStats.h"
#include <cstdlib>

Archer::Archer(const std::string name) : Character(name, archer_stats::MAX_HP, archer_stats::MIN_DMG, archer_stats::MAX_DMG)
{
}

int Archer::calculateDmg(const bool isAbilityBlocked)
{
	int dmg = (rand() % (maxDmg - minDmg + 1)) + minDmg;


	if (isAbilityBlocked)
	{
		std::cout << "[MIRROR] Special ability is blocked!";
		return dmg;
	}

	if (dmg <= 4)
	{
		bool change = changeDmg(dmg);
		if (change == true)
		{
			return 2 * dmg;
		}

	}
	
	return dmg;
}

bool Archer::changeDmg(const int dmg) const
{
	int choice = -1;
	std::cout << "Change damage (From " << dmg << " to " << 2 * dmg << ")?\n";
	std::cout << "YES (1)/ NO (0)";
	std::cin >> choice;

	return choice;
}

std::unique_ptr<Character> Archer::clone() const
{
	return std::make_unique<Archer>(*this);
}