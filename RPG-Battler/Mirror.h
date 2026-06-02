#pragma once
#include "Item.h"

class Mirror : public Item
{
public:
    Mirror();
    void use(Character* target) override;
    std::unique_ptr<Item> clone() const override;

};

