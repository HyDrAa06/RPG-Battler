#pragma once
#include "Character.h"

class Warrior : public Character
{
public:
	Warrior(const std::string name);
	int calculateDmg(bool isAbilityBlocked = false) override;
	void takeDmg(const int dmg, bool isAbilityBlocked = false) override;

	std::unique_ptr<Character> clone() const override;

	virtual int getClassId() const override;

};

