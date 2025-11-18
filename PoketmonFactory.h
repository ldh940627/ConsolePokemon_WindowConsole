#pragma once
#include <memory>
#include <string>
#include "Poketmon.h"


using namespace std;
// 저장을 위한 팩토리
class PoketmonFactory {
public:
    static shared_ptr<Poketmon> Create(const string& name) {
        if (name == "피카츄") return make_shared<picachu>();
        else if (name == "라이츄") return make_shared<raichu>();
        else if (name == "꼬부기") return make_shared<squirtle>();
        else if (name == "어니부기") return make_shared<wartortle>();
        else if (name == "파이리") return make_shared<charmander>();
        else if (name == "리자드") return make_shared<charmeleon>();
        else if (name == "이상해씨") return make_shared<bulbasaur>();
        else if (name == "이상해풀") return make_shared<ivysaur>();
        else if (name == "푸린") return make_shared<jigglypuff>();
        else if (name == "나옹") return make_shared<meowth>();
        else if (name == "고라파덕") return make_shared<psyduck>();
        else if (name == "알통몬") return make_shared<machop>();
        else if (name == "고오스") return make_shared<gastly>();
        else if (name == "코일") return make_shared<magnemite>();
        else if (name == "식스테일") return make_shared<vulpix>();
        else if (name == "모래두지") return make_shared<sandshrew>();
        else if (name == "뚜벅쵸") return make_shared<bellsprout>();
        else if (name == "케이시") return make_shared<abra>();
        else if (name == "갸라도스") return make_shared<gyarados>();
        else if (name == "후딘") return make_shared<alakazam>();
        else if (name == "망나뇽") return make_shared<dragonite>();
        else if (name == "윈디") return make_shared<arcanine>();
        else if (name == "이상해꽃") return make_shared<venusaur>();
        else if (name == "딱구리") return make_shared<golem>();
        else return nullptr;
    }
};

