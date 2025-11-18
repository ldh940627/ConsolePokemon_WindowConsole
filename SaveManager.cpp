#include "SaveManager.h"
#include "PoketmonFactory.h"
#include "ItemFactory.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void SaveManager::SaveGame(const Player& player, const GameMap& map, const string& filename)
{
	ofstream file(filename);
	if (!file.is_open())
	{
		cerr << "[ERROR] 저장 파일을 열 수 없습니다." << endl;
		return;
	}

	file << "map:" << map.GetCurrentMapName() << "\n";
	file << "player:" << player.GetX() << "," << player.GetY() << "\n";

	for (auto it = player.poketmoninventory.poketmons.begin(); it != player.poketmoninventory.poketmons.end(); ++it)
	{
        shared_ptr<Poketmon> p = it->second;
		if (p)
		{
            file << "poketmon : " << p->GetName() << ","
                << p->GetLevel() << ","
                << p->GetMaxHp() << ","
                << p->GetCurrentHp() << ","
                << p->GetExp() << ","
                << p->GetAttack() << ","
                << p->GetDefense() << ","
                << p->GetSpAttack() << ","
                << p->GetSpDefense() << ","
                << p->GetSpeed() << "\n";
		}
	}

	for (const auto& pair : player.iteminventory.GetAllItems())
	{
		file << "item:" << pair.first << "," << pair.second << "\n";
	}

	file.close();
	cout << "게임이 저장되었습니다." << endl;
}

void SaveManager::LoadGame(Player& player, GameMap& map, const string& filename) {
   
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "[ERROR] 저장 파일을 찾을 수 없습니다." << endl;
        return;
    }

    string line;
   

    while (getline(file, line)) {
        
        istringstream ss(line);
        string key;
        getline(ss, key, ':');

        if (!key.empty() && (unsigned char)key[0] == 0xEF) {
            key = key.substr(3);
        }

        key.erase(0, key.find_first_not_of(" \r\n\t"));
        key.erase(key.find_last_not_of(" \r\n\t") + 1);

      
    
        if (key == "map") {
            string mapName;
            getline(ss, mapName);
            map.LoadMap(mapName);
        }
        else if (key == "player") {
            string xStr, yStr;
            getline(ss, xStr, ',');
            getline(ss, yStr);
            player.MoveTo(stoi(xStr), stoi(yStr));
        }
        else if (key == "poketmon") {
            string name, levelStr, maxhpStr, curhpstr, expStr;
            string atkStr, defStr, spatkStr, spdefStr, spdStr;

            getline(ss, name, ',');
            getline(ss, levelStr, ',');
            getline(ss, maxhpStr, ',');
            getline(ss, curhpstr, ',');
            getline(ss, expStr, ',');
            getline(ss, atkStr, ',');
            getline(ss, defStr, ',');
            getline(ss, spatkStr, ',');
            getline(ss, spdefStr, ',');
            getline(ss, spdStr);
            name.erase(0, name.find_first_not_of(" \r\n\t"));
            name.erase(name.find_last_not_of(" \r\n\t") + 1);

           
            // 트림 등 동일하게 처리
            auto p = PoketmonFactory::Create(name);
          
            if (p) {
                p->SetLevel(stoi(levelStr));
                p->SetMaxHp(stoi(maxhpStr));
                p->SetCurrentHp(stoi(curhpstr));
                p->SetExp(stoi(expStr));
                p->SetAttack(stoi(atkStr));
                p->SetDefense(stoi(defStr));
                p->SetSpAttack(stoi(spatkStr));
                p->SetSpDefense(stoi(spdefStr));
                p->SetSpeed(stoi(spdStr));
                player.poketmoninventory.AddCatchPoketmon(p);
            }
           
        }
        else if (key == "item") {
            string name, countStr;
            getline(ss, name, ',');
            getline(ss, countStr);

            auto item = ItemFactory::Create(name);
            if (item) {
                player.iteminventory.AddItem(item, stoi(countStr));
            }
        }
    }

    file.close();
    cout << "게임이 불러와졌습니다." << endl;
}