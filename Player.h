#pragma once  
#include<iostream>  
#include"Trainer.h"  
#include"ItemInventory.h"  

using namespace std;  

class Player : public Trainer  
{
private:
	int x;
	int y;
	int Money;

public:
	Player(string name, int startX, int startY, int Money);
	ItemInventory iteminventory;
	
	// Getter
	int GetX() const;
	int GetY() const;
	int GetMoney() const;

	// function
	void MoveTo(int x, int y); // 플레이어 이동
	bool SpendMoney(int amount); // 돈 사용
	void AddMoney(int amount);  // 돈 추가
	void Allheal(); // 모든 포켓몬 회복
	


}; 