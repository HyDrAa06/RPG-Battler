#pragma once
#include "Character.h"

class Mage : public Character
{
public:
	Mage(const std::string name);
	int calculateDmg() override;
	bool changeDmg(const int dmg) const;

	std::unique_ptr<Character> clone() const override;

};

