#pragma once
#include "Character.h"

class Warrior : public Character
{
public:
	Warrior(const std::string name);
	int calculateDmg() override;
	void takeDmg(const int dmg) override;

	std::unique_ptr<Character> clone() const override;
};

