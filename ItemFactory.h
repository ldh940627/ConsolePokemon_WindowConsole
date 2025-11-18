#pragma once
#include <memory>
#include <string>
#include "Item.h"
#include "Monsterball.h"
#include "HealingItem.h"

using namespace std;
// 저장을 위한 팩토리
class ItemFactory {
public:
    static shared_ptr<Item> Create(const string& name) {
        if (name == "Potion") return make_shared<Potion>();
        if (name == "Hyperball") return make_shared<Hyperball>();
        if (name == "Poketball") return make_shared<Poketball>();
        if (name == "Superball") return make_shared<Superball>();

        return nullptr;
    }
};
