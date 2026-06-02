#include "HealPotion.h"
#include "CharacterStats.h"
#include <cstdlib>

HealPotion::HealPotion() : Item( item_stats::HEAL_POTION_XP, ItemType::HEALING_POTION)
{
}

void HealPotion::use(Character* target)
{
	std::cout << "Used a heal potion: " << std::endl;
	int heal = (rand() % 6) + 5;

	if (target->getHp() + heal >= target->getMaxHp())
	{
		std::cout << "Healed to full hp!\n";
		target->healMax();
	}
	else
	{
		
		std::cout << "Healed to " << target->getHp() + heal << " hp!\n";
		target->setHp(target->getHp() + heal);
	}
}

std::unique_ptr<Item> HealPotion::clone() const
{
	return std::make_unique<Item>(*this);
}
