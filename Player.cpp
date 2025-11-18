#include "Player.h"
#include "UIManager.h"
#include "PoketmonInventory.h"

Player::Player(string name, int startX, int startY, int Money) : Trainer(name), x(startX), y(startY), Money(Money) {}

int Player::GetX() const { return x; }
int Player::GetY() const { return y; }
int Player::GetMoney() const { return Money; }

bool Player::SpendMoney(int amount)
{
	if (Money >= amount)
	{
		Money -= amount;
		return true;
	}
	return false;
}

void Player::AddMoney(int amount)
{
	Money += amount;
}

void Player::MoveTo(int newX, int newY)
{
	x = newX;
	y = newY;
}

void Player::Allheal()
{
	UIManager::GetInstance();
	for (auto& entry : poketmoninventory.poketmons)
	{
		entry.second->SetCurrentHp(entry.second->GetMaxHp());
	}
	system("cls");
	UIManager::GetInstance().ShowMessageBox("모든 포켓몬이 회복되었습니다!");
	
}