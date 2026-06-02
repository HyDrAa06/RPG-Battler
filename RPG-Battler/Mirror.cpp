#include "Mirror.h"
#include "Character.h"
#include <iostream>
#include "CharacterStats.h"

Mirror::Mirror()
    : Item(item_stats::MIRROR_XP, ItemType::MIRROR) {
}

void Mirror::use(Character* target) {
    std::cout << "You have used a mirror:"  << std::endl;
    std::cout << "Your opponent's next attack will be blocked!\n";
}


std::unique_ptr<Item> Mirror::clone() const
{
    return std::make_unique<Item>(*this);
}