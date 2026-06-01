#pragma once
#include "Character.h"

class Archer : public Character
{
public:
	Archer(const std::string name);
	int calculateDmg() override;
	bool changeDmg(const int dmg) const;

	std::unique_ptr<Character> clone() const override;

};

