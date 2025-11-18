#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<windows.h>

using namespace std;

class GameMap
{
private:
	vector<vector<char>> layout;
	string currentMapName;

public :

	const string& GetCurrentMapName() const { return currentMapName; }
	void LoadMap(const string& mapName);
	void draw(int playerX, int playerY) const;
	bool isWalkable(int x, int y) const;
	char GetTile(int x, int y) const;
	void SetTile(int x, int y, char newTile);



};

