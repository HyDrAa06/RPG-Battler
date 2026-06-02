#include "Beam.h"
#include "Character.h"
#include "CharacterStats.h"
#include <iostream>

Beam::Beam()
    : Item(item_stats::BEAM_XP, ItemType::BEAM) {
}

void Beam::use(Character* target) {
    std::cout << "You have used a beam:" << std::endl;
    std::cout << "Your opponent's mirror will break!\n";
}


std::unique_ptr<Item> Beam::clone() const
{
    return std::make_unique<Item>(*this);
}