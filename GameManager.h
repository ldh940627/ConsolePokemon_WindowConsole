#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "GameMap.h"
#include "Trainer.h"

using namespace std;


class GameManager
{
public:

	GameManager();
	void Run();
	

private:
	void LoadTrainersForCurrentMap();
	void HandleEventAt(int x, int y);
	void SelectStarterPoketmon(Player& player);
	
	Player player;
	GameMap map;
	vector<shared_ptr<Trainer>> trainers;
	vector<bool> trainerDefeated;

};

