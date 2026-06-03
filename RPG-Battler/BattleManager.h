#pragma once
#include "User.h"
#include "Character.h"

class BattleManager
{
	User* player1;
	User* player2;

	Character* hero1;
	Character* hero2;

	bool p1BladeActive;
	bool p2BladeActive;
	bool p1MirrorActive;
	bool p2MirrorActive;

	void playTurn(User* attackerUser, Character* attackerHero,
		User* defenderUser, Character* defenderHero,
		bool& attackerBlade,bool& attackerMirror, bool& defenderMirror);

public:
	BattleManager(User* p1, Character* h1, User* p2, Character* h2);

	void start();
};

