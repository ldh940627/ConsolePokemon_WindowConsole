#include<iostream>
#include<map>
#include<memory>
#include<string>
#include<vector>
#include "ItemInventory.h"
#include "Item.h"
#include "Player.h"
#include "Poketmon.h"
#include "Monsterball.h"
#include "UIManager.h"

using namespace std;

shared_ptr<Item> ItemInventory::GetItem(const string& name) const
{
	auto it = items.find(name);
	if (it != items.end()) return it->second.first;
	return nullptr;
}

void ItemInventory::AddItem(shared_ptr<Item> item, int count)
{
	string name = item->GetName();
	if (items.count(name))
	{
		items[name].second += count;
	}
	else
	{
		items[name] = { item, count };
	}
}

bool ItemInventory::BattleUseItem(const string& name, shared_ptr<Poketmon> target)
{
	if (items.count(name) == 0 || items[name].second <= 0)
	{
		
		return false;
	}
	items[name].first->BattleUse(target);
	items[name].second--;

	if (items[name].second == 0)
	{
		items.erase(name);
	}
	
	return true;
}
bool ItemInventory::UseItem(const string& name, shared_ptr<Poketmon> target)
{
	if (items.count(name) == 0 || items[name].second <= 0)
	{

		return false;
	}
	items[name].first->Use(target);
	items[name].second--;

	if (items[name].second == 0)
	{
		items.erase(name);
	}

	return true;
}
bool ItemInventory::UseBall(const string& name)
{
	if (items.count(name) == 0 || items[name].second <= 0)
	{
		cout << "[X] " << name << "이(가) 없습니다!" << endl;
		return false;
	}
	items[name].second--;

	if (items[name].second == 0)
	{
		items.erase(name);
	}
	return true;
 }

const map<string, pair<shared_ptr<Item>, int>>& ItemInventory::GetItems() const
{
	return items;
}
void ItemInventory::DisplayInventory() const
{
	cout << "=== 아이템 인벤토리 ===" << endl;
	for (const auto& entry : items)
	{
		cout << "- " << entry.first << " x" << entry.second.second << endl;
	}
}

map<string, int> ItemInventory::GetAllItems() const
{
	map<string, int> result;
	for (const auto& pair : items)
	{
		result[pair.first] = pair.second.second;
	}
	return result;
}

vector<Item*> ItemInventory::GetItemVector() const
{
	vector<Item*> itemVector;
	for (const auto& pair : items)
	{
		if (pair.second.second > 0)
		itemVector.push_back(pair.second.first.get());
	}
	return itemVector;
}