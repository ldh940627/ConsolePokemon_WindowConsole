#include "Poketmoninventory.h"
#include "Poketmon.h"
#include<vector>

bool Poketmoninventory::AddPoketmon(int id, shared_ptr<Poketmon> poketmon)
{
	if (poketmons.size() >= MAX_SIZE)
	{
		cout << "가진 포켓몬은 6마리를 초과할 수 없습니다! " << endl;
		return false;
	}

	poketmons[id] = poketmon;
	return true;

}

bool Poketmoninventory::AddCatchPoketmon(shared_ptr<Poketmon> poketmon)
{
	if (poketmons.size() >= MAX_SIZE)
	{
		cout << "가진 포켓몬은 6마리를 초과할 수 없습니다! " << endl;
		return false;
	}
	int id = 0;
	while (poketmons.count(id))
	{
		++id;
	}

	poketmons[id] = poketmon;
	cout << poketmon->GetName() << "이(가) 인벤토리에 추가되었습니다! (슬롯 " << id << ")\n";
	return true;
}

shared_ptr<Poketmon> Poketmoninventory::GetPoketmon(int id)
{
	if (poketmons.count(id))
	{
		return poketmons[id];
	}
	else
	{
		return nullptr;
	}
}

shared_ptr<Poketmon> Poketmoninventory::GetFirstAlivePoketmon()
{
	for (const auto& entry : poketmons)
	{
		if (entry.second && !entry.second->IsFainted()) // 기절여부 확인
		{
			return entry.second;
		}
	}
	return nullptr; // 살아있는 포켓몬이 없을 경우 nullptr 반환
}

bool Poketmoninventory::removePoketmon(int id)
{
	auto it = poketmons.find(id);
	if (it != poketmons.end())
	{
		poketmons.erase(it);
		cout << "슬롯 " << id << "의 포켓몬이 삭제되었습니다." << endl;
		return true;
	}
	else
	{
		cout << "해당 슬롯에 포켓몬이 없습니다." << endl;
		return false;
	}
}

void Poketmoninventory::displayPoketmonInventory()
{
	if (poketmons.empty())
	{
		cout << "보유한 포켓몬이 없습니다." << endl;
		return;
	}
	for (const auto& p : poketmons)
	{
		cout << "슬롯" << p.first << ": " << p.second->GetName() << endl;
	}
}

int Poketmoninventory::GetSize() const
{
	int count = 0;
	for (const auto& p : poketmons)
	{
		if (p.second) ++count;
	}
	return count;
}

vector<shared_ptr<Poketmon>> Poketmoninventory::GetPoketmons()
{
	vector<shared_ptr<Poketmon>> result;
	for (auto& pair : poketmons)
		result.push_back(pair.second); // 그대로 shared_ptr
	return result;
}

void Poketmoninventory::ReplacePoketmon(int id, shared_ptr<Poketmon> evolvepoketmon)
{
	if (poketmons.count(id))
	{
		poketmons[id] = evolvepoketmon;
	}
}

int Poketmoninventory::FindSlot(const shared_ptr<Poketmon>& target) const
{
	for (auto it = poketmons.begin(); it != poketmons.end(); ++it)
	{
		if (it->second == target)
		{
			return it->first;
		}
	}
	return -1;
}
