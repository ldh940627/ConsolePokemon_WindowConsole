#pragma once
#include<iostream>
#include<map>
#include<memory>
#include<string>
#include<vector>

class Item;
class Player;
class Poketmon;
class Monsterball;
class UIManager;

using namespace std;


class ItemInventory
{
public:
	map<string, pair<shared_ptr<Item>, int>> items;

public:
	shared_ptr<Item> GetItem(const string& name) const;

	void AddItem(shared_ptr<Item> item, int count = 1);
	bool BattleUseItem(const string& name, shared_ptr<Poketmon> target);
	bool UseItem(const string& name, shared_ptr<Poketmon> target);
	bool UseBall(const string& name);
	const map<string, pair<shared_ptr<Item>, int>>& GetItems() const;
	void DisplayInventory() const;
	map<string, int> GetAllItems() const;
	vector<Item*> GetItemVector() const; // 아이템을 벡터로 반환하는 함수
};