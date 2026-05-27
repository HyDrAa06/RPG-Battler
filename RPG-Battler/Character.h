#pragma once
#include <cstring>
#include <iostream>

class Character
{
protected:
	std::string name;
	int maxHp;
	int currentHp;
	int level;
	int minDmg;
	int maxDmg;
	
public:
	Character(const std::string& name, const int maxHp, const int minDmg, const int maxDmg);
	virtual ~Character() = default;

	void healMax();
	virtual void takeDmg(const int dmg);
	virtual int calculateDmg() =0;

	bool isDead() const;
	int getMaxHp() const;
	int getHp() const;
	int getLevel() const;
	std::string getName() const;

	void setHp(const int amount);

	void levelUp();
	void increaseMaxHp(const int amount);
	void increaseMaxDmg(const int amount);

};

