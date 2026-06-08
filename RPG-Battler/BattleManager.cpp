#include "BattleManager.h"
#include <iostream>
#include <cstdlib>

void BattleManager::playTurn(User* attackerUser, Character* attackerHero, User* defenderUser, Character* defenderHero, bool& attackerBlade, bool& attackerMirror, bool& defenderMirror)
{
	std::cout << "HP: " << attackerHero->getName() << ": " << attackerHero->getHp() << "\n";
	std::cout << "HP: " << defenderHero->getName() << ": " << defenderHero->getHp() << "\n";
	std::cout << "Action: (1: Attack, 2: Use an item): ";

	int choice;
	std::cin >> choice;

	if (choice == 1)
	{
		int attackDmg = attackerHero->calculateDmg(defenderMirror);

		if (defenderMirror)
		{
			defenderMirror = false;
		}

		if (attackerBlade)
		{
			std::cout << "[BLADE] Your DMG is doubled!\n";
			attackDmg *= 2;
			attackerBlade = false;
		}

		if (attackDmg > 0 && defenderUser->hasItem(ItemType::SHIELD))
		{
			std::cout << "[!] " << defenderUser->getUsername() << " you are goning to take"
				<< attackDmg << " dmg! Do you want to use your Shield? (y/n): ";

			char shieldChoice;
			std::cin >> shieldChoice;

			if (shieldChoice == 'y' || shieldChoice == 'Y')
			{
				Item* shield = defenderUser->getItem(ItemType::SHIELD);
				shield->use(defenderHero);

				defenderUser->useItem(ItemType::SHIELD);
				attackDmg = 0;
			}
		}

		if (attackDmg > 0)
		{
			defenderHero->takeDmg(attackDmg, attackerMirror);

			if (attackerMirror)
			{
				attackerMirror = false;
			}	
		}

		
	}
	else if (choice == 2)
	{
		std::cout << "Which item will you use? (1: Potion, 2: Blade, 3: Mirror): \n";
		int itemChoice;
		std::cin >> itemChoice;

		ItemType selectedType;
		if (itemChoice == 1) selectedType = ItemType::HEALING_POTION;
		else if (itemChoice == 2) selectedType = ItemType::BLADE;
		else if (itemChoice == 3) selectedType = ItemType::MIRROR;
		else
		{
			std::cout << "Invalid choice! You lose your turn!\n";
			return;
		}

		Item* itemToUse = attackerUser->getItem(selectedType);

		if (itemToUse != nullptr)
		{
			itemToUse->use(attackerHero);
			if (selectedType == ItemType::BLADE)
			{
				attackerBlade = true;
			}
			else if (selectedType == ItemType::MIRROR)
			{
				if (defenderUser->hasItem(ItemType::BEAM))
				{
					std::cout << "[!] " << defenderUser->getUsername()
						<< ", your opponent has used a mirror. Would you like to use a beam? (y/n): ";
					char beamChoice;
					std::cin >> beamChoice;

					if (beamChoice == 'y' || beamChoice == 'Y')
					{
						Item* beam = defenderUser->getItem(ItemType::BEAM);
						beam->use(defenderHero);

						defenderUser->useItem(ItemType::BEAM);
						attackerMirror = false; 
					}
					else
					{
						attackerMirror = true;
					}
				}
				else 
				{
					attackerMirror = true;
				}
			}

			attackerUser->useItem(selectedType);
		}
		else
		{
			std::cout << "You don't have an item of this type! You lose your turn!\n";
		}
	}
}

BattleManager::BattleManager(User* p1, Character* h1, User* p2, Character* h2) :
	player1(p1), player2(p2), hero1(h1), hero2(h2)
{
}

void BattleManager::start()
{
	std::cout << "\n=== THE BATTLE BEGINS! ===\n";
	std::cout << player1->getUsername() << " (" << hero1->getName() << ") VS"
		<< player2->getUsername() << " (" << hero2->getName() << ")\n";

	bool isPlayerOneTurn = (rand() % 2 == 0);

	while (hero1->getHp() > 0 && hero2->getHp() > 0)
	{
		if (isPlayerOneTurn)
		{
			std::cout << "--- " << player1->getUsername() << "'s turn ---\n";
			playTurn(player1, hero1, player2, hero2, p1BladeActive,p1MirrorActive, p2MirrorActive);
		}
		else
		{
			std::cout << "--- " << player2->getUsername() << "'s turn ---\n";
			playTurn(player2, hero2, player1, hero1, p2BladeActive,p2MirrorActive,  p1MirrorActive);
		}

		isPlayerOneTurn = !isPlayerOneTurn;
	}

	if (hero1->getHp() > 0)
	{
		std::cout << "\nThe winner is " << player1->getUsername() << "!\n";
		player1->addXp(10);
		player2->addXp(5);

		player1->recordMatch(true);
		player2->recordMatch(false);

	}
	else
	{
		std::cout << "\nThe winner is " << player2->getUsername() << "!\n";
		player2->addXp(10);
		player1->addXp(5);

		player2->recordMatch(true);
		player1	->recordMatch(false);
	}

	hero1->healMax();
	hero2->healMax();


}
