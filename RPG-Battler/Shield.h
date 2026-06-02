#pragma once
#include "Item.h"

class Shield : public Item {
public:
    Shield();
    void use(Character* target) override;
    std::unique_ptr<Item> clone() const override;

};