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

	virtual int getClassId() const = 0;

	void healMax();
	virtual void takeDmg(const int dmg, bool isAbilityBlocked = false);
	virtual int calculateDmg(bool isAbilityBlocked = false) =0;

	bool isDead() const;
	int getMaxHp() const;
	int getHp() const;
	int getLevel() const;
	int getMinDmg() const;
	int getMaxDmg() const;
	std::string getName() const;

	void setHp(const int amount);
	void setName(const std::string name);
	void setMaxHp(const int maxHp);
	void setLevel(const int level);
	void setMinDmg(const int minDmg);
	void setMaxDmg(const int maxDmg);


	void levelUp();
	void increaseMaxHp(const int amount);
	void increaseMaxDmg(const int amount);

	virtual std::unique_ptr<Character> clone() const = 0;

};

