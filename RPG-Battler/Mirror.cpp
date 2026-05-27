#include "Mirror.h"
#include "Character.h"
#include <iostream>
#include "CharacterStats.h"

Mirror::Mirror()
    : Item(name, item_stats::MIRROR_XP, ItemType::MIRROR) {
}

void Mirror::use(Character* target) {
    std::cout << "You have used a mirror:" << name << std::endl;
    std::cout << "Your opponent's next attack will be blocked!\n";
}