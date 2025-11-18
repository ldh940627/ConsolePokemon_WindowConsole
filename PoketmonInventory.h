#pragma once
#include<iostream>
#include<map>
#include<memory>
#include<vector>
#include "Poketmon.h"


class Poketmoninventory
{

public:
	
	map<int, shared_ptr<Poketmon>> poketmons;
	static const int MAX_SIZE = 6;

public:

	bool AddPoketmon(int id, shared_ptr<Poketmon> poketmon);
	bool AddCatchPoketmon(shared_ptr<Poketmon> poketmon);
	shared_ptr<Poketmon> GetPoketmon(int id);
	shared_ptr<Poketmon> GetFirstAlivePoketmon();
	bool removePoketmon(int id);
	void displayPoketmonInventory();
	int Size() const { return poketmons.size(); }
	int GetSize() const;  // 저장을 위한함수
	vector<shared_ptr<Poketmon>> GetPoketmons(); // 포켓몬을 벡터로 반환하는 함수
	void ReplacePoketmon(int id, shared_ptr<Poketmon> evolvepoketmon);
	int FindSlot(const shared_ptr<Poketmon>& target) const;
};


