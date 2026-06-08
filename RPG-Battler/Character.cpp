#include "Character.h"

Character::Character(const std::string& name, const int maxHp, const int minDmg, const int maxDmg) : 
	name(name), maxHp(maxHp), minDmg(minDmg), maxDmg(maxDmg), level(1){}

int Character::getClassId() const
{
	return 0;
}

void Character::healMax()
{
	currentHp = maxHp;
}

bool Character::isDead() const
{
	return currentHp <= 0;
}

int Character::getHp() const
{
	return currentHp;
}

int Character::getMaxHp() const
{
	return maxHp;
}

int Character::getLevel() const
{
	return level;
}

int Character::getMaxDmg() const
{
	return maxDmg;
}

int Character::getMinDmg() const
{
	return minDmg;
}

std::string Character::getName() const
{
	return name;
}

void Character::setHp(const int amount)
{
	this->currentHp = amount;
}

void Character::setName(const std::string name)
{
	this->name = name;
}

void Character::setMaxHp(const int maxHp)
{
	this->maxHp = maxHp;
}

void Character::setLevel(const int level)
{
	this->level = level;
}

void Character::setMinDmg(const int minDmg)
{
	this->minDmg = minDmg;
}


void Character::setMaxDmg(const int maxDmg)
{
	this->maxDmg = maxDmg;
}


void Character::takeDmg(const int dmg, bool isAbilityBlocked)
{
	currentHp -= dmg;
	if (currentHp < 0)
		currentHp = 0;
}

int Character::calculateDmg(bool isAbilityBlocked)
{
	return 0;
}

void Character::levelUp()
{
	level++;
}
void Character::increaseMaxHp(const int amount)
{
	maxHp += amount;
	currentHp += amount;
}
void Character::increaseMaxDmg(const int amount)
{
	maxDmg = amount;
}

std::unique_ptr<Character> Character::clone() const
{
	return std::unique_ptr<Character>();
}
