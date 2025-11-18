#include "Store.h"
#include "UIManager.h"

#include <iostream>
#include <conio.h>

Store::Store()
{
	itemsForSale.push_back(make_shared<Potion>());
	prices.push_back(300);

	itemsForSale.push_back(make_shared<Hyperball>());
	prices.push_back(500);

	itemsForSale.push_back(make_shared<Superball>());
	prices.push_back(300);

	itemsForSale.push_back(make_shared<Poketball>());
	prices.push_back(100);

}

void Store::ShowStoreMenu(Player& player)
{
	UIManager::GetInstance();
	int selected = 0;

	while (true)
	{
		UIManager::GetInstance().ClearScreen();
		UIManager::GetInstance().ShowStoreMenu(player, selected);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selected = (selected - 1 + itemsForSale.size()) % itemsForSale.size(); // ↑
			else if (key == 80) selected = (selected + 1) % itemsForSale.size(); // ↓
		}
		else if (key == 'z' || key == 'Z') {
			BuyItem(player, selected);
		}
		else if (key == 'x' || key == 'X') {
			break;
		}
	}
}


void Store::BuyItem(Player& player, int index)
{
	if (player.GetMoney() >= prices[index])
	{
		player.SpendMoney(prices[index]);
		player.iteminventory.AddItem(itemsForSale[index], 1);
		cout << itemsForSale[index]->GetName() << "을(를) 구입했습니다!" << endl;
	}
	else {
		cout << "금액이 부족합니다." << endl;
	}
	system("pause");
	
}