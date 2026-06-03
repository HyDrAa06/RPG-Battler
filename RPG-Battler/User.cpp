#include "User.h"
#include "CharacterStats.h"
#include "Character.h"

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