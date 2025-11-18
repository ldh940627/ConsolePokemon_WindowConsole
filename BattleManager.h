// BattleManager.h
#pragma once
#include <iostream>
#include <memory>
#include <string>



using namespace std;

class Trainer;
class Player;
class Poketmon;
class PoketmonInventory;
class ItemInventory;
class Item;
class GameMap;


class BattleManager 
{
private :
    static GameMap* mapPtr;
    

public:
    
    

    static void SetMap(GameMap* map) { mapPtr = map; };

    // 트레이너 전투
    static void StartBattle(Player& player, Trainer& enemy, bool isWild = false);

    // 야생 포켓몬 전투
    static void StartWildBattle(Player& player, shared_ptr<Poketmon> wild, bool isWild = true);


   
private:
    static bool PlayerTurn(Player& player, shared_ptr<Poketmon>& playerpoketmon, shared_ptr<Poketmon>& target, bool isWild);

    static void EnemyTurn(Trainer* enemy, shared_ptr<Poketmon>& enemypoketmon, shared_ptr<Poketmon>& playerpoketmon);

    static void SkillAttack(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target);

    static bool UseItemDuringBattle(Player& player, shared_ptr<Poketmon>& activepoketmon, shared_ptr<Poketmon>& target, bool isWild);

    static bool SwitchPoketmon(Player& player, shared_ptr<Poketmon>& current);

	static void SwitchPoketmonenemy(Trainer& enemy, shared_ptr<Poketmon>& current);

    static bool TryEscape();
};
