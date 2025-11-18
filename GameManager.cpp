#include "GameManager.h"
#include "UIManager.h"
#include "SaveManager.h"
#include "BattleManager.h"
#include "Poketmon.h"
#include "Wildpoketmongenerator.h"
#include "Item.h"
#include "Monsterball.h"
#include "Store.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

Store store;

using namespace std;

GameManager::GameManager() : player("한지우", 1, 1, 500)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    BattleManager::SetMap(&map);

    player.iteminventory.AddItem(make_shared<Potion>(), 2);
    player.iteminventory.AddItem(make_shared<Hyperball>(), 5);

   

    trainers = {
       make_shared<TrainerChulmin>(),
       make_shared<TrainerJihye>(),
       make_shared<TrainerSangwoo>(),
       make_shared<TrainerMiyeon>()
    };

    map.LoadMap("map1.txt");
    Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
    LoadTrainersForCurrentMap();

}

void GameManager::Run()
{
    UIManager::GetInstance();
    SaveManager savemanager;
    int choice = UIManager::GetInstance().ShowStartMenu();

    switch (choice) {
    case 0:
        UIManager::GetInstance().ShowProfessorIntro();
        SelectStarterPoketmon(player);
        break;
    case 1:
        savemanager.LoadGame(player, map, "save.txt");
        break;
    case 2:
        UIManager::GetInstance().ShowMessageBox("게임을 종료합니다.");
        exit(0);
        break;
    }

    while (true)
    {
        system("cls");
        UIManager::GetInstance().DrawHUD(player, map.GetCurrentMapName());
        UIManager::GetInstance().SetCusorPosition(0, 3);
        map.draw(player.GetX(), player.GetY());

        
        int input = _getch();

        if (input == 224)
        {
            input = _getch();

            int nextX = player.GetX();
            int nextY = player.GetY();

            switch (input)
            {
            case 72: nextY--; break; 
            case 80: nextY++; break; 
            case 75: nextX--; break; 
            case 77: nextX++; break; 
            }

            if (map.isWalkable(nextX, nextY))
            {
                player.MoveTo(nextX, nextY);
                HandleEventAt(nextX, nextY);
            }
        }
        else if (input == 'x' || input == 'X')
        {
            return;
        }
        else if (input == 'm') {
            UIManager::GetInstance().ShowMainMenu(player, map);
        }
    }
}

void GameManager::HandleEventAt(int x, int y)
{

    char tile = map.GetTile(x, y);
    UIManager::GetInstance();

    if (tile == 'G') {
        if (rand() % 100 < 40) {
            auto wild = Wildpoketmongenerator::Generate();
            BattleManager::StartWildBattle(player, wild);
        }
    }
    else if (tile == 'T')
    {
        for (int i = 0; i < trainers.size(); ++i) {
            if (!trainers[i]) continue;

            if (trainers[i]->GetX() == x && trainers[i]->GetY() == y) {
                BattleManager::StartBattle(player, *trainers[i]);
                map.SetTile(x, y, '.');
                break;
            }
        }
    }
    else if (tile == 'L')
    {
        for (int i = 0; i < trainers.size(); ++i) {
            if (!trainers[i]) continue;

            if (trainers[i]->GetX() == x && trainers[i]->GetY() == y) {
                UIManager::GetInstance().ShowGymLeaderIntro();
                BattleManager::StartBattle(player, *trainers[i]);
                map.SetTile(x, y, '.');
                break;
            }
        }
    }
    else if (tile == 'W') {
        UIManager::GetInstance().ShowMessageBox("[맵 이동] 다른 지역으로 이동합니다.");

        if (map.GetCurrentMapName() == "map1.txt") {
            map.LoadMap("map2.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(1, 11);
        }
        else if (map.GetCurrentMapName() == "map2.txt") {
            map.LoadMap("map3.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(1, 7);
        }
        else if (map.GetCurrentMapName() == "map3.txt") {
            map.LoadMap("map4.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(28, 10);
        }
        else if (map.GetCurrentMapName() == "map4.txt") {
            map.LoadMap("map5.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(25, 13);
        }
        else if (map.GetCurrentMapName() == "map5.txt") {
            map.LoadMap("map6.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(15, 13);
        }
        else {
            map.LoadMap("map1.txt");
        }

        LoadTrainersForCurrentMap();        
        
    }
    else if (tile == 'B') {
        UIManager::GetInstance().ShowMessageBox("[맵 이동] 다른 지역으로 이동합니다.");

        if (map.GetCurrentMapName() == "map2.txt") {
            map.LoadMap("map1.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(28, 11);
        }
        else if (map.GetCurrentMapName() == "map3.txt") {
            map.LoadMap("map2.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(28, 7);
        }
        else if (map.GetCurrentMapName() == "map4.txt") {
            map.LoadMap("map3.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(1, 10);
        }
        else if (map.GetCurrentMapName() == "map5.txt") {
            map.LoadMap("map4.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(25, 1);
        }
        else if (map.GetCurrentMapName() == "map6.txt") {
            map.LoadMap("map5.txt");
            Wildpoketmongenerator::SetMapContext(map.GetCurrentMapName());
            player.MoveTo(14, 3);
        }
        else {
            map.LoadMap("map1.txt");
        }

        LoadTrainersForCurrentMap();
        
    }
    else if (tile == 'C')
    {
		player.Allheal();
		
    }
    else if (tile == 'S')
    {
        store.ShowStoreMenu(player);

    }
}

void GameManager::LoadTrainersForCurrentMap() {
    trainers.clear();

    if (map.GetCurrentMapName() == "map2.txt") {
        auto trainer = make_shared<TrainerChulmin>();
        trainer->SetPosition(13, 4); 
        trainers.push_back(trainer);
    }
    else if (map.GetCurrentMapName() == "map3.txt") {
        auto trainer = make_shared<TrainerJihye>();
        trainer->SetPosition(19, 3);
        trainers.push_back(trainer);
    }
    else if (map.GetCurrentMapName() == "map4.txt") {
        auto trainer = make_shared<TrainerSangwoo>();
        trainer->SetPosition(4, 11);
        trainers.push_back(trainer);
    }
    else if (map.GetCurrentMapName() == "map5.txt") {
        auto trainer = make_shared<TrainerMiyeon>();
        trainer->SetPosition(7, 9);
        trainers.push_back(trainer);
    }
    else if (map.GetCurrentMapName() == "map6.txt") {
        auto trainer = make_shared<GymLeader>();
        trainer->SetPosition(15, 1);
        trainers.push_back(trainer);
    }
}


void GameManager::SelectStarterPoketmon(Player& player)
{
    UIManager::GetInstance();
    int selected = 0;
    while (true)
    {
        UIManager::GetInstance().ClearScreen();
        UIManager::GetInstance().DrawStartingPoketmonselecte(selected); 

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + 4) % 4; 
            else if (key == 80) selected = (selected + 1) % 4; 
        }
        else if (key == 'z' || key == 'Z') {
            shared_ptr<Poketmon> chosen;
            if (selected == 0) chosen = make_shared<picachu>();
            else if (selected == 1) chosen = make_shared<charmander>();
            else if (selected == 2) chosen = make_shared<bulbasaur>();
            else if (selected == 3) chosen = make_shared<squirtle>();

            player.poketmoninventory.AddPoketmon(0, chosen);
            UIManager::GetInstance().ShowMessageBox(chosen->GetName() + "(을)를 선택했습니다!");
            break;
        }
    }
}
