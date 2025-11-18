#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "BattleManager.h"
#include "Trainer.h"
#include "Player.h"
#include "Item.h"
#include "GameMap.h"
#include "UIManager.h"	

GameMap* BattleManager::mapPtr = nullptr;


// 트레이너 전투
void BattleManager::StartBattle(Player& player, Trainer& enemy, bool isWild)
{
	system("cls");
	
	shared_ptr<Poketmon> playerpoketmon = player.poketmoninventory.GetFirstAlivePoketmon();
	shared_ptr<Poketmon> enemypoketmon = enemy.poketmoninventory.GetFirstAlivePoketmon();
	shared_ptr<Poketmon> defeatedPoketmon = nullptr;
	UIManager::GetInstance().ShowBattleIntro(enemypoketmon ? enemypoketmon->GetName() : "???", playerpoketmon ? playerpoketmon->GetName() : "???", !isWild);
	UIManager::GetInstance().ShowMessageBox(enemy.GetIntroDialogue());

	if (!playerpoketmon)
	{
		UIManager::GetInstance().ShowMessageBox(player.GetName() + "은(는) 사용할 수 있는 포켓몬이 없습니다!");
		return;
	}

	bool keepFighting = true;

	while (keepFighting)
	{
		if (!playerpoketmon || playerpoketmon->IsFainted()) {
			playerpoketmon = player.poketmoninventory.GetFirstAlivePoketmon();
			if (!playerpoketmon) break;
			UIManager::GetInstance().AddBattleLog(player.GetName() + "이(가) 새로운 포켓몬을 꺼냈습니다!");
		}

		if (!enemypoketmon || enemypoketmon->IsFainted()) {
			defeatedPoketmon = enemypoketmon;
			UIManager::GetInstance().AddBattleLog(enemy.GetName() + "의 " + defeatedPoketmon->GetName() + "이(가) 쓰러졌습니다!");

			if (playerpoketmon && !playerpoketmon->IsFainted()) {
				int gainExp = defeatedPoketmon->GetLevel() * 10;
				playerpoketmon->GainExp(gainExp);
				UIManager::GetInstance().ShowMessageBox("전투에서 승리하여 " + playerpoketmon->GetName() + "이(가) 경험치를" + to_string(gainExp) + "획득했습니다!");
				if (playerpoketmon->CanEvolve(player))
				{
					auto evolved = playerpoketmon->Evolve();
					UIManager::GetInstance().ShowMessageBox(playerpoketmon->GetName() + "이(가)" + evolved->GetName() + " 으로 진화했습니다.");
					int slot = player.poketmoninventory.FindSlot(playerpoketmon);
					player.poketmoninventory.ReplacePoketmon(slot, evolved);
				}
			}

			SwitchPoketmonenemy(enemy, enemypoketmon);
			enemypoketmon = enemy.poketmoninventory.GetFirstAlivePoketmon();
			if (!enemypoketmon) break;
			UIManager::GetInstance().AddBattleLog(enemy.GetName() + "이(가) 새로운 포켓몬을 꺼냈습니다!");
		}

		bool playerfirst = playerpoketmon->GetSpeed() >= enemypoketmon->GetSpeed();

		if (playerfirst) {
			keepFighting = PlayerTurn(player, playerpoketmon, enemypoketmon, false);
			if (!keepFighting || enemypoketmon->IsFainted()) continue;
			EnemyTurn(&enemy, enemypoketmon, playerpoketmon);
		}
		else {
			EnemyTurn(&enemy, enemypoketmon, playerpoketmon);
			if (!playerpoketmon || playerpoketmon->IsFainted()) continue;
			keepFighting = PlayerTurn(player, playerpoketmon, enemypoketmon, false);
		}
	}

	if (!player.poketmoninventory.GetFirstAlivePoketmon()) {
		system("cls");
		UIManager::GetInstance().ShowMessageBox(player.GetName() + "는 눈앞이 캄캄해졌다!");
		UIManager::GetInstance().ShowMessageBox(player.GetName() + "의 포켓몬이 모두 쓰러졌습니다. 패배!");
		if (mapPtr) mapPtr->LoadMap("map1.txt");
		player.MoveTo(10,3);
		player.Allheal();
		system("pause");
	}
	else if (!enemy.poketmoninventory.GetFirstAlivePoketmon()) {
		int reward = enemy.GetRewardMoney();
		player.AddMoney(reward);
		UIManager::GetInstance().ShowMessageBox("전투에서 승리하여" + to_string(reward) + "원을 획득했습니다!");
		UIManager::GetInstance().ShowMessageBox(enemy.GetDefeatDialogue());
		system("pause");
		if (dynamic_cast<GymLeader*>(&enemy))
		{
			system("cls");
			UIManager::GetInstance().ShowMessageBox(" 당신은 관장을 이겼습니다!");
			UIManager::GetInstance().ShowMessageBox(" 모든 모험을 완료했습니다! 축하합니다!");
			exit(0);
		}
	}
}



// 야생 포켓몬 전투
void BattleManager::StartWildBattle(Player& player, shared_ptr<Poketmon> wild, bool isWild) {
	shared_ptr<Poketmon> playerpoketmon = player.poketmoninventory.GetFirstAlivePoketmon();
	
	UIManager::GetInstance().ShowBattleIntro(wild ? wild->GetName() : "???", playerpoketmon ? playerpoketmon->GetName() : "???", !isWild);
	UIManager::GetInstance().ShowMessageBox("전투 시작! " + player.GetName() + " vs 야생 " + wild->GetName());

	bool keepFighting = true;
	while (playerpoketmon && wild && !playerpoketmon->IsFainted() && !wild->IsFainted() && keepFighting) {
		bool playerfirst = playerpoketmon->GetSpeed() >= wild->GetSpeed();

		if (playerfirst) {
			keepFighting = PlayerTurn(player, playerpoketmon, wild, true);
			if (!keepFighting || wild->IsFainted()) break;
			EnemyTurn(nullptr, wild, playerpoketmon);
		}
		else {
			EnemyTurn(nullptr, wild, playerpoketmon);
			if (playerpoketmon->IsFainted()) break;
			keepFighting = PlayerTurn(player, playerpoketmon, wild, true);
			if (!keepFighting || wild->IsFainted()) break;
		}
	}

	if (playerpoketmon->IsFainted()) {
		system("cls");
		UIManager::GetInstance().ShowMessageBox(player.GetName() + "는 눈앞이 캄캄해졌다!");
		UIManager::GetInstance().ShowMessageBox(player.GetName() + "의 포켓몬이 모두 쓰러졌습니다. 패배!");
		if (mapPtr) mapPtr->LoadMap("map1.txt");
		player.MoveTo(10, 3);
		player.Allheal();
		system("pause");
	}
	else if (wild->IsFainted()) {
		UIManager::GetInstance().ShowMessageBox(wild->GetName() + "이(가) 쓰러졌습니다. 승리!");
		int reward = wild->Getreward();
		player.AddMoney(reward);
		int gainExp = wild->GetLevel() * 10;
		playerpoketmon->GainExp(gainExp);
		UIManager::GetInstance().ShowMessageBox("전투에서 승리하여 " + playerpoketmon->GetName() + "이(가) 경험치" + to_string(gainExp) + "을(를) 획득했습니다!");
		UIManager::GetInstance().ShowMessageBox("전투에서 승리하여 " + to_string(reward) + "원을 획득했습니다!");
		if (playerpoketmon->CanEvolve(player))
		{
			auto evolved = playerpoketmon->Evolve();
			UIManager::GetInstance().ShowMessageBox(playerpoketmon->GetName() + "이(가)에" + " 상태가 이상하다!!!");
			UIManager::GetInstance().ShowMessageBox(playerpoketmon->GetName() + "이(가)" + evolved->GetName() + " 으로 진화했습니다.");
			int slot = player.poketmoninventory.FindSlot(playerpoketmon);
			player.poketmoninventory.ReplacePoketmon(slot, evolved);
		}
		
	}
}

bool BattleManager::PlayerTurn(Player& player, shared_ptr<Poketmon>& playerpoketmon, shared_ptr<Poketmon>& target, bool isWild) {
	
	int action = 0;
	UIManager::GetInstance();
	while (true) {
		UIManager::GetInstance().ClearScreen();
		UIManager::GetInstance().DrawBattleStatus(playerpoketmon.get(), target.get());
		UIManager::GetInstance().DrawBattleMenu(action);
		UIManager::GetInstance().DrawBattleLog();

		int input = _getch();
		if (input == 224) {
			input = _getch();
			if (input == 72) action = (action - 1 + 4) % 4;
			else if (input == 80) action = (action + 1) % 4;
		}
		else if (input == 'z' || input == 'Z') {
			break;
		}
	}

	switch (action) {
	case 0:
		SkillAttack(playerpoketmon, target);
		return true;
	case 1:
		return UseItemDuringBattle(player, playerpoketmon, target, isWild);
	case 2:
		return SwitchPoketmon(player, playerpoketmon);
		
	case 3:
		if (isWild || TryEscape()) {
			UIManager::GetInstance().ShowMessageBox("당신은 도망쳤습니다. 전투 종료!");
			return false;
		}
		else {
			UIManager::GetInstance().ShowMessageBox("도망에 실패했습니다!");
			return true;
		}
	default:
		UIManager::GetInstance().ShowMessageBox("잘못된 입력입니다.");
		return true;
	}
}

void BattleManager::EnemyTurn(Trainer* enemy, shared_ptr<Poketmon>& enemypoketmon, shared_ptr<Poketmon>& playerpoketmon) {
	UIManager::GetInstance();
	string ownerName = enemy ? enemy->GetName() : "야생";

	UIManager::GetInstance().AddBattleLog(ownerName + "의 " + enemypoketmon->GetName() + "의 공격!");
	int skillcount = enemypoketmon->skillinventory.GetSkillCount();
	if (skillcount == 0) {
		UIManager::GetInstance().AddBattleLog(enemypoketmon->GetName() + "은(는) 사용할 수 있는 스킬이 없습니다!");
		return;
	}

	int randomindex = rand() % skillcount;
	auto skill = enemypoketmon->skillinventory.GetSkill(randomindex);
	UIManager::GetInstance().AddBattleLog("[AI] 스킬 선택: " + skill->GetName());
	int prevHP = playerpoketmon->GetCurrentHp();
	skill->Use(enemypoketmon, playerpoketmon);
	int damage = prevHP - playerpoketmon->GetCurrentHp();
	UIManager::GetInstance().AddBattleLog(playerpoketmon->GetName() + "은(는) " + to_string(damage) + " 데미지를 입었다!");
}


void BattleManager::SkillAttack(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target) {
	int skillCount = user->skillinventory.GetSkillCount();
	if (skillCount == 0) {
		UIManager::GetInstance().ShowMessageBox(user->GetName() + "은(는) 사용할 수 있는 스킬이 없습니다!");
		return;
	}

	vector<Skill*> skills;
	for (int i = 0; i < skillCount; ++i) {
		auto s = user->skillinventory.GetSkill(i);
		if (s) skills.push_back(s.get());
	}

	int selected = 0;
	while (true) {
		UIManager::GetInstance().ClearScreen();
		UIManager::GetInstance().DrawSkillMenu(skills, selected);
		UIManager::GetInstance().DrawBattleLog(0, 8, 5); // 하단 로그 고정 출력

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selected = (selected - 1 + skillCount) % skillCount;
			if (key == 80) selected = (selected + 1) % skillCount;
		}
		else if (key == 'z' || key == 'Z') break;
	}

	auto skill = skills[selected];
	if (skill) {
		UIManager::GetInstance().AddBattleLog(user->GetName() + "의 " + skill->GetName() + "!");
		int prev = target->GetCurrentHp();
		skill->Use(user, target);
		int damage = prev - target->GetCurrentHp();
		UIManager::GetInstance().AddBattleLog(target->GetName() + "가 " + to_string(damage) + "의 피해를 입었습니다! (HP: " + to_string(target->GetCurrentHp()) + " / " + to_string(target->GetMaxHp()) + ")");
	}
}


bool BattleManager::UseItemDuringBattle(Player& player, shared_ptr<Poketmon>& activepoketmon, shared_ptr<Poketmon>& target, bool isWild) {
	UIManager::GetInstance();
	const vector<Item*>& items = player.iteminventory.GetItemVector();
	if (items.empty()) {
		UIManager::GetInstance().ShowMessageBox("소지한 아이템이 없습니다.");
		return true;
	}

	int selectedItem = 0;

	while (true) {
		UIManager::GetInstance().ClearScreen();
		UIManager::GetInstance().DrawItemMenu(player, selectedItem); // 아이템 선택 메뉴
		UIManager::GetInstance().DrawBattleLog(0, 18, 5);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selectedItem = (selectedItem - 1 + items.size()) % items.size();
			if (key == 80) selectedItem = (selectedItem + 1) % items.size();
		}
		else if (key == 'z' || key == 'Z') break;
	}

	Item* item = items[selectedItem];
	string itemName = item->GetName();

	// 포켓볼류
	if (itemName.find("볼") != string::npos) {
		if (!isWild) {
			UIManager::GetInstance().ShowMessageBox("트레이너의 포켓몬은 포획할 수 없습니다!");
			return true;
		}
		player.iteminventory.UseBall(itemName);
		bool caught = item->WildCatch(target, player);
		return !caught;
	}

	// 회복 아이템류
	// --- 포켓몬 인벤토리 열기 ---
	vector<shared_ptr<Poketmon>> poketmons = player.poketmoninventory.GetPoketmons();
	if (poketmons.empty()) {
		UIManager::GetInstance().ShowMessageBox("사용 가능한 포켓몬이 없습니다!");
		return true;
	}

	int selectedPokemon = 0;

	while (true) {
		UIManager::GetInstance().ClearScreen();
		UIManager::GetInstance().DrawPoketmonMenu(poketmons, selectedPokemon); // 포켓몬 선택창
		UIManager::GetInstance().DrawBattleLog(0, 18, 5);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selectedPokemon = (selectedPokemon - 1 + poketmons.size()) % poketmons.size();
			if (key == 80) selectedPokemon = (selectedPokemon + 1) % poketmons.size();
		}
		else if (key == 'z' || key == 'Z') break;
	}

	shared_ptr<Poketmon> targetPokemon = poketmons[selectedPokemon];
	if (!targetPokemon) {
		UIManager::GetInstance().ShowMessageBox("잘못된 포켓몬 선택입니다.");
		return true;
	}

	bool used = player.iteminventory.BattleUseItem(itemName, targetPokemon);
	if (used) {
		UIManager::GetInstance().AddBattleLog(itemName + "을(를) " + targetPokemon->GetName() + "에게 사용했습니다!");
		
	}

	return true;
}

bool BattleManager::SwitchPoketmon(Player& player, shared_ptr<Poketmon>& current) {
	
	UIManager::GetInstance();
	vector<shared_ptr<Poketmon>> poketmons = player.poketmoninventory.GetPoketmons();
	
	if (poketmons.empty()) {
		UIManager::GetInstance().ShowMessageBox("보유한 포켓몬이 없습니다");
		return true;
	}
	
	int selectedPoktemon = 0;
	while (true) {
		UIManager::GetInstance().ClearScreen();
		UIManager::GetInstance().DrawPoketmonMenu(poketmons, selectedPoktemon); // 포켓몬 선택창
		UIManager::GetInstance().DrawBattleLog(0, 18, 5);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selectedPoktemon = (selectedPoktemon - 1 + poketmons.size()) % poketmons.size();
			if (key == 80) selectedPoktemon = (selectedPoktemon + 1) % poketmons.size();
		}
		else if (key == 'z' || key == 'Z') break;
	}

	shared_ptr<Poketmon> targetPokemon = poketmons[selectedPoktemon];
	if (!targetPokemon) {
		UIManager::GetInstance().ShowMessageBox("잘못된 포켓몬 선택입니다.");
		return true;
	}
		
	if (targetPokemon && !targetPokemon->IsFainted()) {
		current = targetPokemon;
		UIManager::GetInstance().AddBattleLog(targetPokemon->GetName() + "(으)로 교체했습니다!");
		return true;
	}
	else {
		UIManager::GetInstance().AddBattleLog("잘못된 교체 선택입니다!");
	}
}

void BattleManager::SwitchPoketmonenemy(Trainer& enemy, shared_ptr<Poketmon>& current) {
	UIManager::GetInstance();
	auto newpoketmon = enemy.poketmoninventory.GetFirstAlivePoketmon();
	
	if (newpoketmon && !newpoketmon->IsFainted()) {
		current = newpoketmon;
		UIManager::GetInstance().AddBattleLog(enemy.GetName() + "이(가) " + newpoketmon->GetName() + "(으)로 교체했습니다!");
	}
}


bool BattleManager::TryEscape() {
	int chance = rand() % 100;
	return chance < 30;
}
