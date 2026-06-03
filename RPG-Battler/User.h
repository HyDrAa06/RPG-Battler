#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Character.h"
#include "Item.h"
class User
{
	std::string username;
	std::string password;
	int totalXp;
	int unspentXp;
	int matchesPlayed;
	int matchesWon;
	int rankedPlace;
	std::vector<std::unique_ptr<Character>> ownedCharacters;
	std::vector<std::unique_ptr<Item>> ownedItems;


public:

	User(const std::string& username, const std::string& password);

	void addXp(const int amount);
	bool spendXp(const int amount);

	void addHero(std::unique_ptr<Character> character);
	void addItem(std::unique_ptr<Item> item);

	bool buyHero(const Character* prototype, const std::string& name);
	bool buyItem(const Item* prototype);
	bool buyLvlUp(const int heroIndex, int upgradeChoice);

	bool hasItem(const ItemType type) const;
	Item* getItem(const ItemType type);
	void useItem(ItemType type);

	std::string& getUsername();

};

