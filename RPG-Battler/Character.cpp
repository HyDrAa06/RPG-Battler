#include "Character.h"

Character::Character(const std::string& name, const int maxHp, const int minDmg, const int maxDmg) : 
	name(name), maxHp(maxHp), minDmg(minDmg), maxDmg(maxDmg), level(1){}

void Character::healMax()
{
	currentHp = maxHp;
}

bool Character::isDead() const
{
	return currentHp <= 0;
}

void Character::takeDmg(const int dmg)
{
	currentHp -= dmg;
	if (currentHp < 0)
		currentHp = 0;
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

std::string Character::getName() const {
	return name;
}

int Character::getCurrentHp() const {
	return currentHp;
}

int Character::getMaxHp() const {
	return maxHp;
}

int Character::getLevel() const {
	return level;
}