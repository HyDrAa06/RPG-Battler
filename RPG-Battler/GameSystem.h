#pragma once
#include <vector>
#include <cstring>
#include "User.h"

class GameSystem
{
private:
	std::vector<User> allUsers;
	int loggedInUserIndex;
	std::string dataFile;

	void loginUser();
	void registerUser();
	void logoutUser();

	void shopMenu();
	void levelUpMenu();
	void setupBattle();
	void showLeaderboard();

public:
	GameSystem(const std::string& filename);

	void loadData();
	void saveData() const;

	void run();
};

