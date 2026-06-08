#pragma once
#include "Character.h"

class Archer : public Character
{
public:
	Archer(const std::string name);
	int calculateDmg(bool isAbilityBlocked = false) override;
	bool changeDmg(const int dmg) const;
	virtual int getClassId() const override ;


	std::unique_ptr<Character> clone() const override;

};

