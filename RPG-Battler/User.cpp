#include "User.h"

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
	ownedCharacters.push_back(character);
}

void User::addItem(std::unique_ptr<Item> item)
{
	ownedItems.push_back(item);
}
