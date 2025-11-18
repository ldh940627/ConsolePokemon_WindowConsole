#pragma once
#include <iostream>
#include "PoketmonInventory.h"
#include "Poketmon.h"
#include "SkillLibrary.h"


class Trainer
{
private:
	string name;
	int x, y;
    int rewardMoney = 100;

public:
	Poketmoninventory poketmoninventory;
	
	
	Trainer(const string& name, int x = -1, int y = -1);
	virtual ~Trainer() = default;

    // Getter
	virtual string GetName() const { return name; }
    virtual string GetIntroDialogue() const { return name + "이(가) 승부를 걸어왔다!"; }
    virtual string GetDefeatDialogue() const { return name + ": 졌지만 즐거운 승부였어!"; }
	virtual int GetX() const { return x; }
	virtual int GetY() const { return y; }
    virtual int GetRewardMoney() const { return rewardMoney; }
   
    
    void SetRewardMoney(int amount) { rewardMoney = amount; }
    shared_ptr<Poketmon> GetActivePoketmon();
    bool HasAvailablePoketmon();
    void ShowPoketmons();
	void SetPosition(int x, int y);
};

// map2 등장 1단계 포켓몬 레벨 6~8
class TrainerChulmin : public Trainer {
public:
    TrainerChulmin() : Trainer("철민") {
        auto machopPtr = make_shared<machop>("알통몬", 6, 100, "격투", 72, 85, 51, 36, 36, 35);
        machopPtr->skillinventory.AddSkill(SkillLibrary::Headbutt);
        machopPtr->skillinventory.AddSkill(SkillLibrary::Tackle);
        auto gastlyPtr = make_shared<gastly>("고오스", 8, 120, "고스트", 55, 36, 31, 105, 36, 82);
        gastlyPtr->skillinventory.AddSkill(SkillLibrary::ShadowMimic);
        poketmoninventory.AddPoketmon(0, machopPtr);
        poketmoninventory.AddPoketmon(1, gastlyPtr);
    }

    string GetIntroDialogue() const override {
        return "철민: 내 파이팅 정신을 보여주지!";
    }

    string GetDefeatDialogue() const override {
        return "철민: 으윽... 이럴 수가!";
    }
};

// map3 등장 2단계 포켓몬 레벨 9~11
class TrainerJihye : public Trainer {
public:
    TrainerJihye() : Trainer("지혜") {
        auto abraPtr = make_shared<abra>("케이시", 10, 130, "에스퍼", 65, 22, 17, 110, 57, 92);
        abraPtr->skillinventory.AddSkill(SkillLibrary::Psyshock);
        auto vulpixPtr = make_shared<vulpix>("식스테일", 11, 140, "불", 80, 45, 44, 55, 67, 68);
        vulpixPtr->skillinventory.AddSkill(SkillLibrary::Tackle);
        vulpixPtr->skillinventory.AddSkill(SkillLibrary::Ember);
        
        poketmoninventory.AddPoketmon(0, abraPtr);
        poketmoninventory.AddPoketmon(1, vulpixPtr);
    }

    string GetIntroDialogue() const override {
        return "지혜: 내 포켓몬은 지능으로 승부하지!";
    }

    string GetDefeatDialogue() const override {
        return "지혜: 다음엔 절대 안 져!";
    }
};

// map4 등장 3단계 포켓몬 레벨 11~13
class TrainerSangwoo : public Trainer {
public:
    TrainerSangwoo() : Trainer("상우") {
        auto meowthPtr = make_shared<meowth>("나옹", 12, 150, "노말", 100, 48, 38, 42, 42, 95);
        meowthPtr->skillinventory.AddSkill(SkillLibrary::Scratch);
        meowthPtr->skillinventory.AddSkill(SkillLibrary::Bite);
        auto psyduckPtr = make_shared<psyduck>("고라파덕", 13, 155, "물", 120, 56, 50, 75, 52, 57);
        psyduckPtr->skillinventory.AddSkill(SkillLibrary::WaterGun);
        psyduckPtr->skillinventory.AddSkill(SkillLibrary::Psybeam);
        poketmoninventory.AddPoketmon(0, meowthPtr);
        poketmoninventory.AddPoketmon(1, psyduckPtr);
    }

    string GetIntroDialogue() const override {
        return "상우: 돈이 전부가 아니란 걸 보여주지!";
    }

    string GetDefeatDialogue() const override {
        return "상우: 져도 기분은 좋아...";
    }
};

// map5 등장 4단계 포켓몬 레벨 14 ~ 17
class TrainerMiyeon : public Trainer {
public:
    TrainerMiyeon() : Trainer("미연") {
        auto wartortlePtr = make_shared<wartortle>("어니부기", 17, 170, "물", 200, 52, 70, 55, 80, 45);
        wartortlePtr->skillinventory.AddSkill(SkillLibrary::Tackle);
        wartortlePtr->skillinventory.AddSkill(SkillLibrary::BubbleBeam);
        auto bellPtr = make_shared<bellsprout>("뚜벅쵸", 16, 160, "풀", 180, 40, 37, 72, 32, 42);
        bellPtr->skillinventory.AddSkill(SkillLibrary::Growl);
        bellPtr->skillinventory.AddSkill(SkillLibrary::SludgeBomb);
        bellPtr->skillinventory.AddSkill(SkillLibrary::RazorLeaf);
        poketmoninventory.AddPoketmon(0, wartortlePtr);
        poketmoninventory.AddPoketmon(1, bellPtr);
    }

    string GetIntroDialogue() const override {
        return "미연: 귀여운 내 포켓몬들, 가자!";
    }

    string GetDefeatDialogue() const override {
        return "미연: 질 줄은 몰랐어... 다음엔 이길 거야!";
    }
};

class GymLeader : public Trainer {
public:
    GymLeader() : Trainer("관장", 10, 10) {
        poketmoninventory.AddPoketmon(0, make_shared<gyarados>());
        poketmoninventory.AddPoketmon(1, make_shared<alakazam>());
        poketmoninventory.AddPoketmon(2, make_shared<dragonite>());
        poketmoninventory.AddPoketmon(3, make_shared<arcanine>());
        poketmoninventory.AddPoketmon(4, make_shared<venusaur>());
        poketmoninventory.AddPoketmon(5, make_shared<golem>());
    }

    string GetIntroDialogue() const override {
        return "덤벼라!";
    }

    string GetDefeatDialogue() const override {
        return "쳇! 방심했군 다음번엔 봐주지 않겠다!";
    }
};