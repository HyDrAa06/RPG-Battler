#include "Beam.h"
#include "Character.h"
#include "CharacterStats.h"
#include <iostream>

Beam::Beam()
    : Item(name, item_stats::BEAM_XP, ItemType::BEAM) {
}

void Beam::use(Character* target) {
    std::cout << "You have used a beam:" << name << std::endl;
    std::cout << "Your opponent's mirror will break!\n";
}