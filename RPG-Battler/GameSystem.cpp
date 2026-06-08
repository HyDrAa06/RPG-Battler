#include "GameSystem.h"
#include "BattleManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "HealPotion.h"
#include "Blade.h"
#include "Mirror.h"
#include "Shield.h"
#include "Beam.h"

void GameSystem::loginUser()
{
    std::cout << "User: ";
    std::string user;
    std::cin >> user;

    std::cout << "Password: ";
    std::string pass;
    std::cin >> pass;

    for (size_t i = 0; i < allUsers.size(); ++i) {
        if (allUsers[i].getUsername() == user && allUsers[i].checkPassword(pass)) {
            loggedInUserIndex = i;
            std::cout << "Successfully logged in!\n";
            return;
        }
    }
    std::cout << "Invalid username or password!\n";
}

void GameSystem::registerUser()
{
    std::cout << "Enter new username: ";
    std::string user;
    std::cin >> user;

    for (auto& u : allUsers) 
    {
        if (u.getUsername() == user) 
        {
            std::cout << "This username is already taken!\n";
            return;
        }
    }

    std::cout << "Enter new password: ";
    std::string pass;
    std::cin >> pass;

    User newUser(user, pass);

    std::cout << "\nChoose your starting Hero (1: Warrior, 2: Mage, 3: Archer): ";
    int heroChoice;
    std::cin >> heroChoice;

    std::cout << "Enter your Hero's name: ";
    std::string heroName;
    std::cin >> heroName;

    if (heroChoice == 1) newUser.addHero(std::make_unique<Warrior>(heroName));
    else if (heroChoice == 2) newUser.addHero(std::make_unique<Mage>(heroName));
    else if (heroChoice == 3) newUser.addHero(std::make_unique<Archer>(heroName));
    else 
    {
        std::cout << "Invalid choice! You get a Warrior by default.\n";
        newUser.addHero(std::make_unique<Warrior>(heroName));
    }

    std::cout << "\nChoose your starting Item:\n";
    std::cout << "1: Healing Potion\n2: Blade\n3: Mirror\n4: Shield\n5: Beam\nChoice: ";
    int itemChoice;
    std::cin >> itemChoice;

    if (itemChoice == 1) newUser.addItem(std::make_unique<HealPotion>());
    else if (itemChoice == 2) newUser.addItem(std::make_unique<Blade>());
    else if (itemChoice == 3) newUser.addItem(std::make_unique<Mirror>());
    else if (itemChoice == 4) newUser.addItem(std::make_unique<Shield>());
    else if (itemChoice == 5) newUser.addItem(std::make_unique<Beam>());
    else {
        std::cout << "Invalid choice! You get a Healing Potion by default.\n";
        newUser.addItem(std::make_unique<HealPotion>());
    }

    allUsers.push_back(std::move(newUser));
    std::cout << "Registration successful! You can now log in.\n";
}

void GameSystem::logoutUser()
{
    loggedInUserIndex = -1;
    std::cout << "Logged out.\n";
}

void GameSystem::shopMenu()
{
    std::cout << "\n=== MARKET ===\n";
    std::cout << "Unspent XP: " << allUsers[loggedInUserIndex].getUnspentXp() << "\n";
    std::cout << "1. Buy a Hero (50 XP)\n";
    std::cout << "2. Buy an Item\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Which hero? (1: Warrior, 2: Mage, 3: Archer): ";
        int heroChoice;
        std::cin >> heroChoice;

        std::cout << "Enter hero's name: ";
        std::string name;
        std::cin >> name;

        bool success = false;
        if (heroChoice == 1) { Warrior w("temp"); success = allUsers[loggedInUserIndex].buyHero(&w, name); }
        else if (heroChoice == 2) { Mage m("temp"); success = allUsers[loggedInUserIndex].buyHero(&m, name); }
        else if (heroChoice == 3) { Archer a("temp"); success = allUsers[loggedInUserIndex].buyHero(&a, name); }

        if (success) std::cout << "Hero successfully purchased!\n";
    }
    else if (choice == 2)
    {
        std::cout << "Which item? (1: Potion, 2: Blade, 3: Mirror, 4: Shield, 5: Beam): ";
        int itemChoice;
        std::cin >> itemChoice;

        bool success = false;
        if (itemChoice == 1) { HealPotion p; success = allUsers[loggedInUserIndex].buyItem(&p); }
        else if (itemChoice == 2) { Blade b; success = allUsers[loggedInUserIndex].buyItem(&b); }
        else if (itemChoice == 3) { Mirror m; success = allUsers[loggedInUserIndex].buyItem(&m); }
        else if (itemChoice == 4) { Shield s; success = allUsers[loggedInUserIndex].buyItem(&s); }
        else if (itemChoice == 5) { Beam b; success = allUsers[loggedInUserIndex].buyItem(&b); }

        if (success) std::cout << "Item successfully purchased!\n";
    }
}

void GameSystem::levelUpMenu()
{
    std::cout << "\n=== LEVEL UP ===\n";
    std::cout << "Unspent XP: " << allUsers[loggedInUserIndex].getUnspentXp() << "\n";

    allUsers[loggedInUserIndex].printHeroes();

    std::cout << "Enter the index of the hero you want to upgrade: ";
    int heroIndex;
    std::cin >> heroIndex;

    std::cout << "Choose upgrade (1: +2 Max HP, 2: +1 Max DMG): ";
    int upgradeChoice;
    std::cin >> upgradeChoice;

    if (allUsers[loggedInUserIndex].buyLvlUp(heroIndex, upgradeChoice))
    {
        std::cout << "Hero successfully leveled up!\n";
    }
}

void GameSystem::setupBattle()
{
    if (allUsers.size() < 2)
    {
        std::cout << "Not enough players for a fight!\n";
        return;
    }
    std::cout << "Who do you want to challenge? ";
    std::string opponentName;
    std::cin >> opponentName;

    if (opponentName == allUsers[loggedInUserIndex].getUsername()) {
        std::cout << "You can't fight yourself!\n";
        return;
    }

    User* opponent = nullptr;
    for (auto& user : allUsers)
    {
        if (user.getUsername() == opponentName)
        {
            opponent = &user;
            break;
        }
    }

    if (opponent == nullptr)
    {
        std::cout << "A player with this name doesn't exist!\n";
        return;
    }

    std::cout << "\nChose your character: (index):\n";
    int myHeroIndex;
    std::cin >> myHeroIndex;

    Character* myHero = allUsers[loggedInUserIndex].getHero(myHeroIndex);
    if (!myHero) 
    {
        std::cout << "Invalid hero!\n";
        return;
    }

    std::cout << "\nChose a character for your opponent: \n";
    int oppHeroIndex;
    std::cin >> oppHeroIndex;

    Character* oppHero = opponent->getHero(oppHeroIndex);
    if (!oppHero) 
    {
        std::cout << "Invalid hero!\n";
        return;
    }

    BattleManager battle(&allUsers[loggedInUserIndex], myHero, opponent, oppHero);
    battle.start();
}

void GameSystem::showLeaderboard()
{
    if (allUsers.empty()) {
        std::cout << "No players registered yet!\n";
        return;
    }

    std::vector<User*> sortedUsers;
    for (auto& u : allUsers)
    {
        sortedUsers.push_back(&u);
    }

    std::sort(sortedUsers.begin(), sortedUsers.end(), [](User* a, User* b) 
        {
        if (a->getMatchesWon() != b->getMatchesWon()) 
        {
            return a->getMatchesWon() > b->getMatchesWon();
        }
        if (a->getTotalXp() != b->getTotalXp())
        {
            return a->getTotalXp() > b->getTotalXp();
        }
        return a->getWinrate() > b->getWinrate();
        });

    std::cout << "\n=== GLOBAL RANKLIST ===\n";
    int rank = 1;
    for (User* userr : sortedUsers)
    {
        std::cout << rank++ << ". " << userr->getUsername()
            << " | Wins: " << userr->getMatchesWon()
            << " | Total XP: " << userr->getTotalXp()
            << " | Win Rate: " << userr->getWinrate() << "%\n";
    }
}

GameSystem::GameSystem(const std::string& filename) : loggedInUserIndex(-1), dataFile(filename)
{
}

void GameSystem::loadData()
{
    std::ifstream in(dataFile);
    if (!in.is_open()) return;

    size_t usersCount;
    in >> usersCount;

    allUsers.clear();
    for (size_t i = 0; i < usersCount; ++i)
    {
        User tempUser("temp", "temp");
        tempUser.loadFile(in);
        allUsers.push_back(std::move(tempUser));
    }
    in.close();
}

void GameSystem::saveData() const
{
    std::ofstream out(dataFile);
    if (!out.is_open()) return;

    out << allUsers.size() << "\n";
    for (const auto& u : allUsers) 
    {
        u.saveFile(out);
    }
    out.close();
}

void GameSystem::run()
{
	loadData();

	bool isRunning = true;
	while (isRunning)
	{
        if (loggedInUserIndex == -1)
        {
            std::cout << "\n=== RPG BATTLER ===\n";
            std::cout << "1. Login\n";
            std::cout << "2. Register\n";
            std::cout << "3. Ranklist\n";
            std::cout << "4. Exit\n";
            std::cout << "Choice: ";

            int choice;
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid command!\n";
                continue;
            }

            if (choice == 1)
            {
                loginUser();
            }
            else if (choice == 2)
            {
                registerUser();
            }
            else if (choice == 3)
            {
                showLeaderboard();
            }
            else if (choice == 4)
            {
                isRunning = false;
            }
            else
            {
                std::cout << "Invalid command!\n";
            }

        }
        else
        {
            std::cout << "\n=== Profile: " << allUsers[loggedInUserIndex].getUsername() << " ===\n";
            std::cout << "1. Market (Buy a Hero/an Item)\n";
            std::cout << "2. Level up a Hero\n";
            std::cout << "3. Join a FIGHT\n";
            std::cout << "4. Logout\n";
            std::cout << "Choice: ";

            int choice;
            std::cin >> choice;

            if (choice == 1)
            {
                shopMenu();
            }
            else if (choice == 2)
            {
                levelUpMenu();
            }
            else if (choice == 3)
            {
                setupBattle();
            }
            else if (choice == 4)
            {
                logoutUser();
            }
            else
            {
                std::cout << "Invalid command!\n";
            }
        }

        saveData();
        
	}
}
