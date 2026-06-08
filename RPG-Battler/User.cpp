#include "User.h"
#include "CharacterStats.h"
#include "Character.h"
#include <iostream>
#include <fstream>
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "HealPotion.h"
#include "Shield.h"
#include "Mirror.h"
#include "Beam.h"
#include "Blade.h"

User::User(const std::string& username, const std::string& password) : username(username), password(password),
	totalXp(0), unspentXp(0), matchesPlayed(0), matchesWon(0)
{

}

void User::addXp(const int amount)
{
	totalXp += amount;
	unspentXp += amount;
}

bool User::spendXp(const int amount)
{
	if (unspentXp < amount)
	{
		return false;
	}

	unspentXp -= amount;
	return true;
}

void User::addHero(std::unique_ptr<Character> character)
{
	ownedCharacters.push_back(std::move(character));
}

void User::addItem(std::unique_ptr<Item> item)
{
	ownedItems.push_back(std::move(item));
}

bool User::buyHero(const Character* prototype, const std::string& name)
{
	int heroCost = cost::HERO_COST;

	if (!spendXp(heroCost))
	{
		return false;
	}

	std::unique_ptr<Character> clone = prototype->clone();
	clone->setName(name);
	ownedCharacters.push_back(std::move(clone));

	return true;
}

bool User::buyItem(const Item* prototype)
{
	int itemCost = prototype->getPrice();
	if (!spendXp(itemCost))
	{
		return false;
	}

	std::unique_ptr<Item> clone = prototype->clone();
	ownedItems.push_back(std::move(clone));

	return true;
}

bool User::buyLvlUp(const int heroIndex, int upgradeChoice)
{
	if (heroIndex < 0 || heroIndex >= ownedCharacters.size())
	{
		return false;
	}
	if (!spendXp(cost::LVL_UP_COST))
	{
		return false;
	}

	if (upgradeChoice == 1)
	{
		ownedCharacters[heroIndex]->increaseMaxHp(upgrade::HP_UPGRADE);
	}
	else
	{
		ownedCharacters[heroIndex]->increaseMaxDmg(upgrade::DMG_UPGRADE);
	}

	ownedCharacters[heroIndex]->levelUp();
	return true;
	
}

bool User::hasItem(const ItemType type) const
{
	for (auto& item : ownedItems)
	{
		if (item->getType() == type)
		{
			return true;
		}
	}

	return false;
}

Item* User::getItem(const ItemType type)
{
	for (const auto& item : ownedItems)
	{
		if (item->getType() == type) return item.get();
	}
	return nullptr;
}

std::string& User::getUsername()
{
	return username;
}

void User::saveFile(std::ofstream& out) const
{
	out << username << " " << password << " " << totalXp << " " << unspentXp 
		<< " " << matchesPlayed << " " << matchesWon <<"\n";

	out << ownedCharacters.size() << "\n";
	for (const auto& hero : ownedCharacters)
	{
		out << hero->getClassId() << " "
			<< hero->getName() << " "
			<< hero->getMaxHp() << " "
			<< hero->getHp() << " "
			<< hero->getLevel() << " "
			<< hero->getMinDmg() << " "
			<< hero->getMaxDmg() << "\n";
	}

	out << ownedItems.size() << "\n";
	for (const auto& item : ownedItems)
	{
		out << static_cast<int>(item->getType()) << "\n";
	}
}

void User::loadFile(std::ifstream& in)
{
	in >> username >> password >> totalXp >> unspentXp >> matchesPlayed >> matchesWon;

	size_t heroesCount;
	in >> heroesCount;

	ownedCharacters.clear();

	for (size_t i = 0;i < heroesCount; ++i)
	{
		int classId, maxHp, hp, level, minDmg, maxDmg;
		std::string heroName;

		in >> classId >> heroName >> maxHp >> hp >> level >> minDmg >> maxDmg;
		std::unique_ptr<Character> newHero;

		if (classId == 1) 
		{
			newHero = std::make_unique<Warrior>(heroName);
		}
		else if (classId == 2)
		{
			newHero = std::make_unique<Mage>(heroName);
		}
		else if (classId == 3)
		{
			newHero = std::make_unique<Archer>(heroName);
		}

		if (newHero)
		{
			newHero->setMaxHp(maxHp);
			newHero->setHp(hp);
			newHero->setLevel(level);
			newHero->setMinDmg(minDmg);
			newHero->setMaxDmg(maxDmg);

			ownedCharacters.push_back(std::move(newHero));
		}

		size_t itemsCount;
		in >> itemsCount;
		ownedItems.clear();

		for (int i = 0;i < itemsCount;++i)
		{
			int typeInt;
			in >> typeInt;
			ItemType type = static_cast<ItemType>(typeInt);
			
			std::unique_ptr<Item> newItem;

			if (type == ItemType::HEALING_POTION) newItem = std::make_unique<HealPotion>();
			else if (type == ItemType::BLADE) newItem = std::make_unique<Blade>();
			else if (type == ItemType::MIRROR) newItem = std::make_unique<Mirror>();
			else if (type == ItemType::SHIELD) newItem = std::make_unique<Shield>();
			else if (type == ItemType::BEAM) newItem = std::make_unique<Beam>();

			if (newItem)
			{
				ownedItems.push_back(std::move(newItem));
			}
		}

	}
}

void User::recordMatch(bool isWinner)
{
	matchesPlayed++;
	if (isWinner)
	{
		matchesWon++;
	}
}

void User::useItem(ItemType type)
{
	for (auto item = ownedItems.begin();item != ownedItems.end();++item)
	{
		if ((*item)->getType() == type)
		{
			ownedItems.erase(item);
			return;
		}
	}
}