#pragma once
#include "Item.h"

class Beam : public Item {
public:
    Beam();
    void use(Character* target) override;
};

