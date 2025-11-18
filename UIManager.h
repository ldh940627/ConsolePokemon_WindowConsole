#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;

class Poketmon;
class Item;
class Skill;
class Player;
class SaveManager;
class GameMap;

class UIManager
{
private:
	int cursorX, cursorY;
	vector<string> battlelog;    // 전투 로그 저장 벡터
	UIManager();
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;

public:
	
	static UIManager& GetInstance();

	// 기본 콘솔 제어
	void ClearScreen();
	void SetCusorPosition(int x, int y);
	void HideCursor();
	void ShowCursor();


	// UI 요소 출력
	void DrawTitleArt(int startX, int startY);
	void DrawStartMenu(int startX, int startY, int selectedIndex);
	void DrawStartingPoketmonselecte(int selected);
	void DrawMainMenu(int selectedIndex);
	void DrawHUD(const Player& player, const string& mapName);
	void DrawBattleMenu(int selectedIndex);
	void DrawPoketmonStatus(const vector<shared_ptr<Poketmon>> Poketmons);
	void DrawPoketmonMenu(const vector<shared_ptr<Poketmon>> Poketmons, int selectedIndex);
	void DrawSkillMenu(const vector<Skill*>& skills, int selectedIndex);
	int SelectSkillToReplace(const vector<shared_ptr<Skill>>& currentSkills, const shared_ptr<Skill>& newSkill);
	void DrawItemMenu(const Player&player, int selectedIndex);
	void DrawBattleLayout(const string& leftName, const string& rightName);
	void FlashEffect(int times = 3, int delay = 100);
	void ShowBattleIntro(const string& enemyname, const string& playerpoketmonname, bool isTrainer);
	void DrawBattleStatus(Poketmon* playerPoketmon, Poketmon* enemyPoketmon);
	void ShowLevelUPUI(const string& name, int oldlevel, int newlevel, int hpGain, int atkGain, int defGain, int spdGain, int apatkGain, int apdefGain);
	void ShowMainMenu(Player&player, GameMap&map);
	void ShowStoreMenu(const Player& player, int selected);
	int ShowStartMenu();
	void ShowProfessorIntro();
	void DrawProfessorArt(int startX, int startY);
	void ShowGymLeaderIntro();
	void DrawGymLeaderArt(int startX, int startY);
	void ShowMessageBox(const string& message);
	void AddBattleLog(const string& log);
	void DrawBattleLog(int x = 0, int y = 15, int maxLines = 5);
	vector<string> WrapText(const string& text, int maxWidth); // 텍스트 줄바꿈 처리
	

	// 입력 처리
	int GetMenuInput(int menuSize);

	// 기타

	void DrawFrame(int x, int y, int width, int height);  // 테두리 그리기
};

