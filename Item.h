#pragma once
#include <iostream>
#include <string>
#include <memory>

class Poketmon;
class Player;
class UIManager;

using namespace std;


class Item 
{
protected:
    string name;
    int count;

public:
    Item(string name, int count = 1) : name(name), count(count) {}
    virtual ~Item() {}
    virtual void BattleUse(shared_ptr<Poketmon> target) = 0; // 회복계 아이템 전용
    virtual void Use(shared_ptr<Poketmon> target) = 0;
    virtual bool WildCatch(shared_ptr<Poketmon> target, Player& player) { return false; }
    virtual string GetName() const = 0;
    virtual int GetCount() const { return count; };
};


