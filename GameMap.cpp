#include "GameMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "ConsoleUtils.h"

void GameMap::LoadMap(const string& filename)
{
    layout.clear();
    currentMapName = filename;

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "[ERROR] 맵 파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        layout.push_back(row);
    }

    file.close();
}



void GameMap::draw(int playerX, int playerY) const
{
    for (int y = 0; y < layout.size(); ++y)
    {
        cout << "          "; // ← 여기 공백 추가 (12칸 정도, 조정 가능)

        for (int x = 0; x < layout[y].size(); ++x)
        {
            if (x == playerX && y == playerY) {
                SetColor(9); // 밝은 파랑: 플레이어
                cout << '@';
            }
            else {
                char tile = layout[y][x];
                switch (tile) {
                case 'G': SetColor(10); break; // Grass
                case 'T': SetColor(12); break; // Trainer
                case 'L': SetColor(13); break; // Gym Leader
                case 'S': SetColor(14); break; // Store
                case 'C': SetColor(11); break; // Center
                case 'W': SetColor(3); break;  // Warp next
                case 'B': SetColor(5); break;  // Warp back
                case '.': SetColor(7); break;  // Empty
                default: SetColor(8); break;   // 기타
                }
                cout << tile;
            }
        }

        SetColor(7); // 기본 색상으로 초기화
        cout << " "  << endl;
    }
    SetColor(7); // 끝나고 색 초기화
}

bool GameMap::isWalkable(int x, int y) const
{
    if (y < 0 || y >= layout.size() || x < 0 || x >= layout[y].size())
        return false;

    char tile = layout[y][x];
    return tile == '.' || tile == 'G' || tile == 'T' || tile == 'W' || tile == 'C' || tile == 'S' || tile == 'L' || tile =='B';
}


char GameMap::GetTile(int x, int y) const
{
    return layout[y][x];
}

void GameMap::SetTile(int x, int y, char newTile)
{
    if (y >= 0 && y < layout.size() &&
        x >= 0 && x < layout[y].size()) {
        layout[y][x] = newTile;
    }
}
