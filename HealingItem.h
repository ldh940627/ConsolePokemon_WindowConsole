#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Item.h"

using namespace std;
// -------------------- Healing Item --------------------
class HealingItem : public Item
{
private:
    int healAmount;

public:
    HealingItem(string name, int amount) : Item(name), healAmount(amount) {}

    string GetName() const override { return name;}

    void BattleUse(shared_ptr<Poketmon> target) override;
    void Use(shared_ptr<Poketmon> target) override;
    
};


class Potion : public HealingItem {
public:
    Potion() : HealingItem("상처약", 30) {} // 회복량은 필요 시 조절
};


