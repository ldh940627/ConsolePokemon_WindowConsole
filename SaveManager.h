#pragma once
#include <string>
#include "Player.h"
#include "GameMap.h"

// 게임 저장 및 로드
class SaveManager
{
public:
	static void SaveGame(const Player& player, const GameMap& map, const string& filename);
	static void LoadGame(Player& player, GameMap& map, const string& filename);
};

