#include "Trainer.h"
#include "Poketmon.h"


Trainer::Trainer(const string& name, int x, int y) : name(name), x(x), y(y) {}

shared_ptr<Poketmon> Trainer::GetActivePoketmon()
{
	return poketmoninventory.GetFirstAlivePoketmon();
}

 bool Trainer::HasAvailablePoketmon()
{
	return poketmoninventory.GetFirstAlivePoketmon() != nullptr;
}

void Trainer::ShowPoketmons()
{
	cout << "[" << name << "의 포켓몬]" << endl;
	poketmoninventory.displayPoketmonInventory();
}

void Trainer::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
