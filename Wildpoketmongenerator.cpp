#include "Wildpoketmongenerator.h"
#include "GameMap.h"

vector<function<shared_ptr<Poketmon>()>> Wildpoketmongenerator::currentWildTable;


void Wildpoketmongenerator::SetMapContext(const string& mapName)
{
    currentWildTable.clear();
    if (mapName == "map1.txt") {
        currentWildTable = {
            []() { return make_shared<vulpix>(5); },
            []() { return make_shared<gastly>(5); },
            []() { return make_shared<krabby>(6); },
            []() { return make_shared<abra>(4); },
            []() { return make_shared<magnemite>(6); },
            []() { return make_shared<jigglypuff>(6); },
            []() { return make_shared<machop>(5); },
            []() { return make_shared<bellsprout>(5); },
            []() { return make_shared<squirtle>(5); },
            []() { return make_shared<bulbasaur>(5); },
            []() { return make_shared<charmander>(5); },

        };
    }
    if (mapName == "map2.txt") {
        currentWildTable = {
            []() { return make_shared<doduo>(9); },
            []() { return make_shared<geodude>(8); },
            []() { return make_shared<rattata>(8); },
            []() { return make_shared<voltorb>(8); },
            []() { return make_shared<nidoran>(9); },
            []() { return make_shared<krabby>(7); },
            []() { return make_shared<bellsprout>(10); },
            []() { return make_shared<slowpoke>(10); },
        };
    }
    if (mapName == "map3.txt") {
        currentWildTable = {
            []() { return make_shared<machop>(11); },
            []() { return make_shared<psyduck>(12); },
            []() { return make_shared<squirtle>(10); },
            []() { return make_shared<ponyta>(12); },
            []() { return make_shared<krabby>(13); },
            []() { return make_shared<doduo>(12); },
            []() { return make_shared<vulpix>(11); },
            []() { return make_shared<nidoran>(11); },
        };
    }
    if (mapName == "map4.txt") {
        currentWildTable = {
            []() { return make_shared<doduo>(14); },
            []() { return make_shared<grimer>(15); },
            []() { return make_shared<zubat>(14); },
            []() { return make_shared<krabby>(16); },
            []() { return make_shared<magnemite>(14); },
            []() { return make_shared<abra>(15); },
            []() { return make_shared<nidoran>(17); },
            []() { return make_shared<ponyta>(16); },
        };
    }
    if (mapName == "map5.txt") {
        currentWildTable = {
            []() { return make_shared<vulpix>(18); },
            []() { return make_shared<jigglypuff>(20); },
            []() { return make_shared<meowth>(16); },
            []() { return make_shared<picachu>(18); },
            []() { return make_shared<ekans>(16); },
            []() { return make_shared<shellder>(20); },
            []() { return make_shared<voltorb>(20); },
            []() { return make_shared<sandshrew>(20); },
        };
    }
    else {
        cout << "[경고] 해당 맵 이름과 일치하는 야생 테이블 없음!" << endl;
    }

}

shared_ptr<Poketmon> Wildpoketmongenerator::Generate()
{
    if (currentWildTable.empty()) return nullptr;
    int index = rand() % currentWildTable.size();
    return currentWildTable[index]();
}
