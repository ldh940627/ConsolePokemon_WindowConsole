#include "UIManager.h"
#include "Poketmon.h"
#include "Item.h"
#include "Player.h"
#include "GameMap.h"
#include "SaveManager.h"
#include "Skill.h"
#include "ConsoleUtils.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>


UIManager::UIManager() : cursorX(0), cursorY(0) {}


UIManager& UIManager::GetInstance()
{
	static UIManager instance;
	return instance;
}

void UIManager::ClearScreen()
{
	system("cls");
}

void UIManager::SetCusorPosition(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UIManager::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void UIManager::ShowCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void UIManager::DrawTitleArt(int startX, int startY) {
	vector<string> titleArt = {
"                                 ,'\\ ",
"    _.----.        ____         ,'  _\\   ___    ___     ____ ",
" _,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`. ",
" \\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  | ",
"  \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  | ",
"    \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  | ",
"     \\     ,-'/  /   \\    ,'   | \\/ / ,`. |         /  /   \\  |     | ",
"      \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    | ",
"       \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   | ",
"        \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   | ",
"         \\_.'       |__|    `-._ |              '-.|     '-.| |   | ",
"                                 `'                            '-._| ",
"                                                                      ",
"                                POKEMON AD                                "
	};

	for (int i = 0; i < titleArt.size(); ++i) {
		
		if (i == titleArt.size() - 2)
			SetColor(14);  
		else if (i == titleArt.size() - 1)
			SetColor(11);  
		else
			SetColor(7);   

		cout << titleArt[i] << endl;
	}

	SetColor(7); 
}
void UIManager::DrawStartMenu(int startX, int startY, int selectedIndex)
{
	ClearScreen();
	DrawTitleArt(2, 1);

	vector<string> menu = { "새로운 게임 시작", "이어하기 (불러오기)", "게임 종료" };

	int menuOffsetY = 16;
	int menuStartY = startY + menuOffsetY;
	int menuStartX = startX + 25;

	for (int i = 0; i < menu.size(); ++i)
	{
		SetCusorPosition(menuStartX, menuStartY + i);
		if (i == selectedIndex)
			cout << ">";
		else
			cout << "";
		cout << menu[i];
	}
}

void UIManager::DrawStartingPoketmonselecte(int selected)
{
	vector<string> starters = { "피카츄", "파이리", "이상해씨", "꼬부기" };
	vector<string> icons = { "전기", "불", "풀", "물" };

	SetCusorPosition(15, 5);
	cout << "원하는 스타팅 포켓몬을 선택하세요!";

	for (int i = 0; i < starters.size(); ++i) {
		SetCusorPosition(15, 7 + i * 2); 

		if (i == selected)
			cout << "> ";
		else
			cout << "  ";

		cout << "[" << starters[i] << "] " << icons[i];
	}

	SetCusorPosition(15, 17);
	cout << "↑ ↓ 키로 이동, Z 키로 선택";
}


void UIManager::DrawMainMenu(int selecetedIndex)
{
	vector<string> menu = { "1. 포켓몬", "2. 가방", "3. 저장하기", "4. 게임종료" };

	ClearScreen();
	DrawFrame(0, 0, 30, menu.size() + 2);

	for (int i = 0; i < menu.size(); ++i)
	{
		SetCusorPosition(2, i + 1);
		if(i== selecetedIndex)
			cout << "-> " << menu[i];
		else
			cout << "   " << menu[i];
	}
}

void UIManager::DrawHUD(const Player& player, const string& mapName)
{
	SetCusorPosition(0, 0);
	cout << "┌─────────────────────────────────────────────────────┐";
	SetCusorPosition(0, 1);
	cout << "│ 이름: " << player.GetName()
		<< "    돈 : " << player.GetMoney() << "원"
		<< "    위치: " << mapName << " (" << player.GetX() << ", " << player.GetY() << ") │";
	SetCusorPosition(0, 2);
	cout << "└─────────────────────────────────────────────────────┘";
}

int UIManager::GetMenuInput(int menuSize)
{
	int selectedIndex = 0;
	while (true)
	{
		DrawMainMenu(selectedIndex);
			

		int key = _getch();
		if (key == 224)
		{
			key = _getch();
			if (key == 72) 
			{
				selectedIndex = (selectedIndex - 1 + menuSize) % menuSize;
			}
			else if (key == 80) 
			{
				selectedIndex = (selectedIndex + 1) % menuSize;
			}
		}
		else if (key == 'z' || key =='Z') 
		{
			return selectedIndex;
		}
		else if (key == 'x' || key == 'X') 
		{
			return -1;
		}
	}
}

void UIManager::DrawFrame(int x, int y, int width, int height)
{
	for (int i = 0; i < width; ++i)
	{
		SetCusorPosition(x + i, y);
		cout << "-";
		SetCusorPosition(x + i, y + height);
		cout << "-";
	}
	for (int i = 0; i < height; ++i)
	{
		SetCusorPosition(x, y + i);
		cout << "|";
		SetCusorPosition(x + width, y + i);
		cout << "|";
	}
	SetCusorPosition(x, y); cout << "┌";
	SetCusorPosition(x + width - 1, y); cout << "┐";
	SetCusorPosition(x, y + height - 1); cout << "└";
	SetCusorPosition(x + width - 1, y + height - 1); cout << "┘";
}

void UIManager::DrawBattleMenu(int selectedIndex)
{
	vector<string> menu = { " 공격 ", " 아이템 ", " 포켓몬 ", " 도망간다 " };
	int x = 0, y = 8, width = 30, height = static_cast<int>(menu.size()) + 2;
	DrawFrame(x, y, width, height);

	for (int i = 0; i < menu.size(); ++i) {
		SetCusorPosition(x + 2, y + 1 + i);
		if (i == selectedIndex)
			cout << "-> ";
		else
			cout << "   ";
		cout << i + 1 << ". " << menu[i];
	}
}

void UIManager::DrawPoketmonStatus(const vector<shared_ptr<Poketmon>> poketmons)
{
	ClearScreen();
	DrawFrame(0, 0, 60, poketmons.size() * 3 + 2);

	for (int i = 0; i < poketmons.size(); ++i)
	{
		SetCusorPosition(2, i * 3 + 1);
		cout << "[" << i + 1 << "] " << poketmons[i]->GetName()
			<< "  Lv." << poketmons[i]->GetLevel();
		SetCusorPosition(2, i * 3 + 2);
		cout << "HP: " << poketmons[i]->GetCurrentHp() << "/" << poketmons[i]->GetMaxHp();
	}
}

void UIManager::DrawSkillMenu(const vector<Skill*>& skills, int selected) {
	int x = 0, y = 0, width = 40, height = skills.size() + 2;
	DrawFrame(x, y, width, height);

	for (int i = 0; i < skills.size(); ++i) {
		SetCusorPosition(x + 2, y + 1 + i);
		if (i == selected) cout << "-> ";
		else cout << "   ";

		cout << i + 1 << ". " << skills[i]->GetName() << " (위력: " << skills[i]->GetPower() << ")";
	}
}

int UIManager::SelectSkillToReplace(const vector<shared_ptr<Skill>>& currentSkills, const shared_ptr<Skill>& newSkill)
{
	int selected = 0;
	while (true) {
		ClearScreen();

		cout << "기존 기술 중 하나를 잊고 \"" << newSkill->GetName() << "\"을(를) 배우시겠습니까?" << endl;
		cout << "↓ ↑ 방향키로 이동, Z 선택, X 취소" << endl;

		vector<Skill*> skillPtrs;
		for (auto& s : currentSkills) skillPtrs.push_back(s.get());
		DrawSkillMenu(skillPtrs, selected);

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selected = (selected - 1 + currentSkills.size()) % currentSkills.size(); // 위
			else if (key == 80) selected = (selected + 1) % currentSkills.size(); // 아래
		}
		else if (key == 'z' || key == 'Z') {
			return selected;
		}
		else if (key == 'x' || key == 'X') {
			return -1;
		}
	}
}

void UIManager::DrawItemMenu(const Player& player, int selectedIndex) {
	ClearScreen();

	const auto& itemMap = player.iteminventory.GetItems();
	DrawFrame(0, 0, 50, itemMap.size() + 2);

	int i = 0;
	for (auto it = itemMap.begin(); it != itemMap.end(); ++it, ++i) {
		SetCusorPosition(2, i + 1);
		if (i == selectedIndex)
			cout << "> ";
		else
			cout << "  ";


		const string& itemName = it->first;
		int itemCount = it->second.second;

		cout << itemName << " x" << itemCount;
	}
}

void UIManager::DrawBattleLayout(const string& leftName, const string& rightName)
{
	const int totalWidth = 44; 
	const int nameZoneWidth = 18; 
	const int vsZoneWidth = 8;

	
	string left = leftName;
	string right = rightName;

	
	int leftPad = nameZoneWidth - left.length() * 2;
	int rightPad = nameZoneWidth - right.length() * 2;

	
	leftPad = max(0, leftPad);
	rightPad = max(0, rightPad);

	cout << "\n+--------------------------------------------+\n";
	cout << "|";

	cout << " " << left << string(leftPad, ' ');
	cout << "   VS   ";
	cout << string(rightPad, ' ') << right;

	cout << " |\n";
	cout << "+--------------------------------------------+\n";
}


void UIManager::FlashEffect(int times, int delay)
{
	for (int i = 0; i < times; ++i)
	{
		system("cls");
		SetColor(15); 
		cout << "\n\n\n\n\n\t\t전투가 시작된다!\n";
		Sleep(delay);

		system("cls");
		SetColor(8); 
		cout << "\n\n\n\n\n\t\t전투가 시작된다!\n";
		Sleep(delay);
	}
	SetColor(15); 
	system("cls");
}



void UIManager::ShowBattleIntro(const string& enemyname, const string& playerpoketmonname, bool isTrainer)
{
	ClearScreen();
	if (isTrainer)
	{
		cout << "" << endl;
		Sleep(800);
		cout << "트레이너가 승부를 걸어왔다!\n";
		Sleep(800);
		cout << "" << endl;
		Sleep(800);
		cout << "트레이너의 포켓몬 " << enemyname << " 이(가) 나타났다!\n";
		cout << "" << endl;
	}
	else
	{
		cout << "" << endl;
		Sleep(800);
		cout << "풀숲에서 무언가가 나타났다...\n";
		Sleep(800);
		cout << "" << endl;
		Sleep(800);
		cout << "야생의 " << enemyname << " 이(가) 나타났다!\n";
		cout << "" << endl;
	}

	Sleep(800);
	cout << "당신은 " << playerpoketmonname << " 을(를) 내보냈다!\n";
	Sleep(800);

	DrawBattleLayout(playerpoketmonname, enemyname);

	Sleep(1000);
	FlashEffect(); 
	ClearScreen();
}



void UIManager::DrawPoketmonMenu(const vector<shared_ptr<Poketmon>> poketmons, int selectedIndex) {
	ClearScreen();
	DrawFrame(0, 0, 50, poketmons.size() + 2);
	for (int i = 0; i < poketmons.size(); ++i) {
		SetCusorPosition(2, i + 1);
		if (i == selectedIndex)
			cout << "> ";
		else
			cout << "  ";
		cout << poketmons[i]->GetName() << " Lv." << poketmons[i]->GetLevel() << " HP: " << poketmons[i]->GetCurrentHp() << "/" << poketmons[i]->GetMaxHp();
	}
}

void UIManager::DrawBattleStatus(Poketmon* playerPoketmon, Poketmon* enemyPoketmon) 
{
	
	int x = 0;
	int y = 0;
	int width = 50;
	int height = 7;

	DrawFrame(x, y, width, height);

	SetCusorPosition(x + 2, y + 1);
	cout << "상대: " << enemyPoketmon->GetName() << " Lv." << enemyPoketmon->GetLevel();

	SetCusorPosition(x + 2, y + 2);
	cout << "HP: " << enemyPoketmon->GetCurrentHp() << " / " << enemyPoketmon->GetMaxHp();

	SetCusorPosition(x + 2, y + 4);
	cout << "내 포켓몬: " << playerPoketmon->GetName() << " Lv." << playerPoketmon->GetLevel();

	SetCusorPosition(x + 2, y + 5);
	cout << "HP: " << playerPoketmon->GetCurrentHp() << " / " << playerPoketmon->GetMaxHp();
}

void UIManager::ShowLevelUPUI(const string& name, int oldLevel, int newLevel,
	int hpGain, int atkGain, int defGain,
	int spdGain, int apatkGain, int apdefGain)
{
	const int width = 48;
    const int height = 10;
    const int x = 30; 
    const int y = 8;

	DrawFrame(x, y, width, height);

	SetCusorPosition(x + 2, y + 1);
	cout << name << "의 레벨이 올랐습니다!";

	SetCusorPosition(x + 2, y + 2);
	cout << "Lv " << oldLevel << " → Lv " << newLevel;

	
	SetCusorPosition(x + 2, y + 4);
	cout << " HP     +" << hpGain;

	SetCusorPosition(x + 2, y + 5);
	cout << " ATK    +" << atkGain;

	SetCusorPosition(x + 2, y + 6);
	cout << " DEF    +" << defGain;

	SetCusorPosition(x + 2, y + 7);
	cout << " SPD    +" << spdGain;

	SetCusorPosition(x + 26, y + 4);
	cout << "APATK   +" << apatkGain;

	SetCusorPosition(x + 26, y + 5);
	cout << "APDEF   +" << apdefGain;

	
	string msg = "계속하려면 아무 키나 누르십시오...";
	int msgX = x + (width - msg.length()) / 2;
	SetCusorPosition(msgX, y + height);
	cout << msg;

	_getch();

}

void UIManager::ShowMainMenu(Player& player, GameMap& map)
{
	SaveManager savemanager;


	int selected = GetMenuInput(4);
	switch (selected)
	{
	case 0:
		DrawPoketmonStatus(player.poketmoninventory.GetPoketmons());
		_getch();
		break;
	case 1:{
		
		const vector<Item*>& items = player.iteminventory.GetItemVector();
		if (items.empty()) {
			ShowMessageBox("사용 가능한 아이템이 없습니다.");
			break;
		}
		int selectedItem = 0;
		while (true)
		{
			DrawItemMenu(player, selectedItem);
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

		vector<shared_ptr<Poketmon>> poketmons = player.poketmoninventory.GetPoketmons();
		if (poketmons.empty()) {
			ShowMessageBox("포켓몬이 없습니다.");
			break;
		}
		int selectedPokemon = 0;

		while (true) {
			ClearScreen();
			DrawPoketmonMenu(poketmons, selectedPokemon); 
			
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
			ShowMessageBox("잘못된 포켓몬 선택입니다.");
		}

		bool used = player.iteminventory.UseItem(itemName, targetPokemon);
		if (used) {
			ShowMessageBox(itemName + "을(를) " + targetPokemon->GetName() + "에게 사용했습니다!");
		}
		else
			ShowMessageBox("아이템 사용에 실패했습니다.");
		break;
		}
	case 2:
		savemanager.SaveGame(player, map, "save.txt");
		break;
	case 3:
		exit(0);
	}
}

void UIManager::ShowStoreMenu(const Player& player, int selected)
{
	vector<string> items = { "상처약", "포켓볼","슈퍼볼","하이퍼볼" };
	vector<int> prices = { 300,100,300,500 };

	ClearScreen();
	DrawFrame(0, 0, 40, 10);

	SetCusorPosition(2, 1);
	cout << "=== 포켓몬 상점 ===";

	for (int i = 0; i < items.size(); ++i) {
		SetCusorPosition(2, 3 + i);
		if (i == selected) cout << "> ";
		else cout << "  ";

		cout << items[i] << " - " << prices[i] << "원";
	}

	SetCusorPosition(2, 8);
	cout << "소지금: " << player.GetMoney() << "원";

	SetCusorPosition(2, 10);
	cout << "↑ ↓ 방향키로 선택, Z 키로 구매, X 키로 나가기";

}

int UIManager::ShowStartMenu()
{
	int selected = 0;
	int startX = 0;
	int startY = 0;
	while (true)
	{
		DrawStartMenu(startX, startY, selected);
		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) selected = (selected - 1 + 3) % 3;
			if (key == 80) selected = (selected + 1) % 3;
		}
		else if (key == 'z' || key == 'Z') {
			return selected;
		}
	}
}

void UIManager::ShowProfessorIntro() {
	ClearScreen();

	
	int artX = 8;
	int artY = 1;
	DrawProfessorArt(artX, artY);

	
	ShowMessageBox("안녕! 나는 이 세계의 포켓몬 박사, '오박사' 라네!");
	ShowMessageBox("이 세계에는 수많은 포켓몬이 존재하고,");
	ShowMessageBox("사람들은 그들과 함께 모험을 떠나지.");
	ShowMessageBox("자, 이제 너도 나만의 포켓몬을 선택할 시간이야!");
}

void UIManager::DrawProfessorArt(int x, int y) {
	vector<string> art = {
	"        ,....................@                      ",
	"       ,.............................,              ",
	"        *,...........................,.             ",
	"          ,......./(%%(....&%&&&&&&.,,,/            ",
	"         @,,,,..........,#..........,,,*            ",
	"          .,,,.,....................,,,             ",
	"          &,,,(@%%%%%&.......%%%%%%%,,.             ",
	"            @,,,@ .(  ....... &@  ,,,,.             ",
	"           &%&,..  % ........  #  ,.,**.            ",
	"            .(,.........*...........,@.             ",
	"              ,........#*...........,               ",
	"              @................./...#               ",
	"                .....#///////(.....%                ",
	"                  *......,,.....,                   ",
	"                  //,&......,&,///                  ",
	"                ,,////*******/////&,,%              ",
	"           %.%,,,////////**&///////*,,%  &.         ",
	"     &,....         ,//////#/#//#////@/*     ..#.   ",
	"  .           &     /,,,,,@//////&,,@,/,     /    & ",
	" .              ..# #,,,,&,,,,,,,,**,,/, ,         &",
	".  *          @     %,,,,,,,&,,,///////.     @      "
	};
	for (int i = 0; i < art.size(); ++i) {
		SetCusorPosition(x, y + i);
		cout << art[i];
	}
}

void UIManager::ShowGymLeaderIntro() {
	ClearScreen();

	
	int artX = 8;
	int artY = 1;
	DrawGymLeaderArt(artX, artY);

	
	ShowMessageBox("후후… 여기까지 오다니, 생각보다 끈질기군.");
	ShowMessageBox("나는 이 체육관의 관장, 가장 강한 트레이너 '레오'다.");
	ShowMessageBox("하지만 네 수준으로 날 이길 수 있을 거라 생각하나?");
	ShowMessageBox("흥미롭군… 짓밟아 주지.");
}

void UIManager::DrawGymLeaderArt(int startX, int startY)
{
	cout << R"( 
                                                 
                        ,                        
                   #**#**** ***                  
               %****************/%               
             .@/**************//#                
               ////(/**#*#*/&//////              
             (%&//**. .  (#   (((                
              ,(((  /&       .&*&&               
                 ,           ,*,                 
                      #(*   *##&                 
                    &  .(*#**                    
                    #*,.***,(##&%&               
              *&,*@#(  ,,,,,,@*,,,,,.            
             ,%,,,,&*&(/(#&,,,,.%,,,/            
            /,,,,,,,&,%%%%,*,,,.,,&,,,#          
            (*,,,,,,,&,%%,&,(,,,,,,,,,*//        
           /////,,,,,,&**/,,,,,/,,,,,,,*/&/,     
          ///////,,,,,,&#,,,,,,,,(,,**/////.     
  # #/   /////& #,,,,,,,,,,,,,,,#  (/////*        
  ###  ////(/*  ,,,,,,,,,,,,,,,,(                 
)" << endl;
}


void UIManager::ShowMessageBox(const string& message) {
	const int x = 0;
	const int y = 20;
	const int width = 80;  
	const int height = 3;

	
	for (int i = 0; i < height; ++i) {
		SetCusorPosition(x, y + i);
		cout << string(width, ' ');
	}

	
	DrawFrame(x, y, width, height);
	SetCusorPosition(x + 2, y + 1);
	cout << message;

	_getch();
}

void UIManager::AddBattleLog(const string& log)
{
	battlelog.push_back("- " + log);
	if (battlelog.size() > 5) {
		battlelog.erase(battlelog.begin()); 
	}
}


void UIManager::DrawBattleLog(int x, int y, int maxLines) {
	DrawFrame(x, y, 70, maxLines + 2); 

	int lineIndex = 0;
	for (int i = max((int)battlelog.size() - maxLines, 0); i < battlelog.size(); ++i) {
		vector<string> wrapped = WrapText(battlelog[i], 66); 

		for (const auto& line : wrapped) {
			SetCusorPosition(x + 2, y + 1 + lineIndex++);
			cout << line;
			if (lineIndex >= maxLines) return;
		}
	}
}


vector<string> UIManager::WrapText(const string& text, int maxWidth) {
	vector<string> lines;
	string line;
	for (char c : text) {
		line += c;
		if (line.length() >= maxWidth) {
			lines.push_back(line);
			line.clear();
		}
	}
	if (!line.empty()) lines.push_back(line);
	return lines;
}