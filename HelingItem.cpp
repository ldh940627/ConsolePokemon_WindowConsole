#include "HealingItem.h"
#include "Item.h"
#include "Player.h"
#include "Poketmon.h"
#include "UIManager.h"  



void HealingItem::BattleUse(shared_ptr<Poketmon> target) {
	if (target) {
		target->Heal(healAmount);
		UIManager::GetInstance();
		UIManager::GetInstance().AddBattleLog(target->GetName() + "의 HP가 " + to_string(healAmount) + " 회복되었습니다!");

	}
}

void HealingItem::Use(shared_ptr<Poketmon> target)
{
	if (target) {
		target->Heal(healAmount);
		UIManager::GetInstance();
		UIManager::GetInstance().ShowMessageBox(target->GetName() + "의 HP가 " + to_string(healAmount) + " 회복되었습니다!");

	}
}