
#include <iostream>
#include <string>
#include <memory>
#include "Monsterball.h"
#include "Player.h"
#include "Poketmon.h"
#include "UIManager.h"

using namespace std;

Monsterball::Monsterball(string name, int catchRate)
    : Item(name), catchRate(catchRate) {
}

bool Monsterball::WildCatch(shared_ptr<Poketmon> target, Player& player) {
    UIManager::GetInstance();
    system("cls");

    UIManager::GetInstance().ShowMessageBox(name + "을(를) 사용했습니다!");

    float hpRatio = static_cast<float>(target->GetCurrentHp()) / target->GetMaxHp();
    int roll = rand() % 100;

    string statusMsg = "포획 시도 중... (남은 HP 비율: " + to_string(hpRatio) +
        ", 포획 확률: " + to_string((1.0f - hpRatio) * catchRate) + "%)";
    UIManager::GetInstance().ShowMessageBox(statusMsg);

    if (roll <= (1.0f - hpRatio) * catchRate) {
        UIManager::GetInstance().ShowMessageBox(target->GetName() + "을(를) 포획했습니다!");

        if (!player.poketmoninventory.AddCatchPoketmon(target)) {
            UIManager::GetInstance().ShowMessageBox("⚠ 인벤토리가 가득 찼습니다!");
        }
        else {
            auto active = player.poketmoninventory.GetFirstAlivePoketmon();
            if (active) {
                int gainExp = target->GetLevel() * 10;
                active->GainExp(gainExp);
                // 경험치 획득 시 메시지는 GainExp 내부에서 처리됨
            }
        }
        return true;
    }
    else {
        UIManager::GetInstance().ShowMessageBox(target->GetName() + "이(가) 몬스터볼을 튕겨냈다!");
        return false;
    }
}


bool Monsterball::Catch(shared_ptr<Poketmon> target) {
    float hpRatio = static_cast<float>(target->GetCurrentHp()) / target->GetMaxHp();
    int roll = rand() % 100;
    return roll <= (1.0f - hpRatio) * catchRate;
}



