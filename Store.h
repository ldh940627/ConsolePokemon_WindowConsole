#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Item.h"
#include "Player.h"
#include "Monsterball.h"
#include "HealingItem.h"

using namespace std;

class Store
{
private:

	vector<shared_ptr<Item>> itemsForSale;
	vector<int> prices;

public:
	Store();
	void ShowStoreMenu(Player& player);
	void BuyItem(Player& player, int index);
};

