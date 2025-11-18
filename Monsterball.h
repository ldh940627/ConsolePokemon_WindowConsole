#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Item.h"


using namespace std;


class Monsterball : public Item {
private:
    int catchRate;

public:
    Monsterball(string name , int catchRate);

    string GetName() const override {
        return name;
    }
    
    void BattleUse(shared_ptr<Poketmon> target) override {}
    void Use(shared_ptr<Poketmon> target) override {}
    bool WildCatch(shared_ptr<Poketmon> target, Player& player) override;

    // 단독 포획 시도 (테스트용 or 확률 시뮬)
    bool Catch(shared_ptr<Poketmon> target);
};

// 확장 아이템 클래스 : 포켓볼
class Poketball : public Monsterball
{
public:
    Poketball() : Monsterball("포켓볼", 50) {}
};


// 확장 아이템 클래스: 슈퍼볼
class Superball : public Monsterball {
public:
    Superball() : Monsterball("슈퍼볼", 75) {}
};

// 확장 아이템 클래스: 하이퍼볼

constexpr const char* HYPERBALL_NAME = "하이퍼볼";

class Hyperball : public Monsterball {
public:
    Hyperball() : Monsterball(HYPERBALL_NAME, 90) {}
};