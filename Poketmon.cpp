#include<iostream>
#include<cstdlib>
#include "Poketmon.h"
#include "SkillLibrary.h"
#include "UIManager.h"
#include "Player.h"
#include "Skill.h"
#include "SkillInventory.h"



using namespace std;

Poketmon::Poketmon(const string& name, int level, int exp, const string& type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: name(name), level(level), exp(exp), type(type), maxhp(hp), currenthp(hp), attack(atk), defense(def),
	spattack(spatk), spdefense(spdef), speed(spd) {
}

void Poketmon::GainExp(int amount)
{
	exp += amount;

	while (exp >= RequiredExpForNextLevel())
	{
		exp -= RequiredExpForNextLevel();
		levelUp();
	}
}

int Poketmon::RequiredExpForNextLevel() const
{
	return level * 20;
}

void Poketmon::levelUp()
{
	int oldlevel = level;
	
	level++;
	CheckLearnableSkills();

	int hpGain = 5 + rand() % 3;
	int atkGain = 2 + rand() % 2;
	int defGain = 2 + rand() % 2;
	int spdGain = 2 + rand() % 2;
	int apatkGain = 2 + rand() % 2;
	int apdefGain = 2 + rand() % 2;

	maxhp += hpGain;
	attack += atkGain;
	defense += defGain;
	speed += spdGain;
	spattack += apatkGain;
	spdefense += apdefGain;
	
	
	// UI 출력
	UIManager::GetInstance();
	system("cls");
	UIManager::GetInstance().ShowLevelUPUI(name, oldlevel, level,
		hpGain, atkGain, defGain, spdGain, apatkGain, apdefGain);
}


void Poketmon::CheckLearnableSkills() 
{
	UIManager::GetInstance();
	if (levelUpSkillTable.count(level)) {
		vector<shared_ptr<Skill>> newSkills = levelUpSkillTable[level];

		for (auto& newSkill : newSkills) {
			UIManager::GetInstance().ShowMessageBox(name + "은(는) 새로운 기술 \"" + newSkill->GetName() + "\"을(를) 배우려 한다!");

			if (skillinventory.IsFull()) {
				int choice = UIManager::GetInstance().SelectSkillToReplace(skillinventory.GetSkills(), newSkill);

				if (choice >= 0) {
					skillinventory.ReplaceSkill(choice, newSkill);
					UIManager::GetInstance().ShowMessageBox(name + "은(는) \"" + newSkill->GetName() + "\"을(를) 배웠다!");
				}
				else {
					UIManager::GetInstance().ShowMessageBox(name + "은(는) \"" + newSkill->GetName() + "\"을(를) 배우지 않았다.");
				}
			}
			else {
				skillinventory.AddSkill(newSkill);
				UIManager::GetInstance().ShowMessageBox(name + "은(는) \"" + newSkill->GetName() + "\"을(를) 배웠다!");
			}
		}
	}
}


void Poketmon::TakeDamage(int amount)
{
	currenthp -= amount;
	if (currenthp < 0) currenthp = 0;
	
}

void Poketmon::Heal(int amount)
{
	currenthp += amount;
	if (currenthp > maxhp) currenthp = maxhp;
}

// 기본 진화 불가능 처리
bool Poketmon::CanEvolve(Player& player) const { return false; }
shared_ptr<Poketmon> Poketmon::Evolve() const { return nullptr; }


picachu::picachu() : Poketmon("피카츄", 5, 100, "전기", 50, 55, 30, 50, 40, 90) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	skillinventory.AddSkill(SkillLibrary::Thunderbolt);
	levelUpSkillTable[10].push_back(SkillLibrary::QuickAttack);
	
}
bool picachu::CanEvolve(Player& player) const { return GetLevel() >= 20; }
shared_ptr<Poketmon> picachu::Evolve() const {
	auto evolved = make_shared<raichu>();
	evolved->skillinventory = this->skillinventory; 
	return evolved;
}

raichu::raichu() : Poketmon("라이츄", 20, 120, "전기", 60, 90, 55, 90, 80, 110) {
	
	levelUpSkillTable[21].push_back(SkillLibrary::Thunder);
}


squirtle::squirtle() : Poketmon("꼬부기", 5, 100, "물", 44, 48, 65, 50, 64, 43) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	skillinventory.AddSkill(SkillLibrary::WaterGun);	
	levelUpSkillTable[10].push_back(SkillLibrary::QuickAttack);
}
bool squirtle::CanEvolve(Player& player) const { return GetLevel() >= 16; }
shared_ptr<Poketmon> squirtle::Evolve() const {
	auto evolved = make_shared<wartortle>();
	evolved->skillinventory = this->skillinventory;
	return evolved;
}

wartortle::wartortle() : Poketmon("어니부기", 16, 120, "물", 220, 63, 80, 65, 80, 58) {
	levelUpSkillTable[17].push_back(SkillLibrary::Bite);
}
bool wartortle::CanEvolve(Player& player) const { return GetLevel() >= 36; }
shared_ptr<Poketmon> wartortle::Evolve() const {
	auto evolved = make_shared<blastoise>();
	evolved->skillinventory = this->skillinventory;
	return evolved;
}


blastoise::blastoise() : Poketmon("거북왕", 36, 265, "물", 530, 83, 100, 85, 105, 78) {
		
	levelUpSkillTable[40].push_back(SkillLibrary::HydroPump);
	levelUpSkillTable[45].push_back(SkillLibrary::WaterCannon);
}


charmander::charmander() : Poketmon("파이리", 5, 100, "불", 45, 52, 43, 60, 50, 65) {
	skillinventory.AddSkill(SkillLibrary::Scratch);
	skillinventory.AddSkill(SkillLibrary::Ember);
	levelUpSkillTable[7].push_back(SkillLibrary::Flamethrower);
	
	
}
bool charmander::CanEvolve(Player& player) const { return GetLevel() >= 16; }
shared_ptr<Poketmon> charmander::Evolve() const {
	auto evolved = make_shared<charmeleon>();
	evolved->skillinventory = this->skillinventory;
	return evolved;
}

charmeleon::charmeleon() : Poketmon("리자드", 16, 120, "불", 180, 64, 58, 80, 65, 80) {
	levelUpSkillTable[17].push_back(SkillLibrary::Bite);
}
bool charmeleon::CanEvolve(Player& player) const { return GetLevel() >= 36; }
shared_ptr<Poketmon> charmeleon::Evolve() const {
	auto evolved = make_shared<charizard>();
	evolved->skillinventory = this->skillinventory;
	return evolved;
}


charizard::charizard() : Poketmon("리자몽", 36, 266, "불꽃", 534, 84, 78, 109, 85, 100) {
	
	levelUpSkillTable[36].push_back(SkillLibrary::WingAttack);
	levelUpSkillTable[42].push_back(SkillLibrary::HeatWave);
	levelUpSkillTable[50].push_back(SkillLibrary::FlareBlitz);
}

bulbasaur::bulbasaur() : Poketmon("이상해씨", 5, 100, "풀", 45, 49, 49, 65, 65, 45) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	
	levelUpSkillTable[6].push_back(SkillLibrary::RazorLeaf);
	levelUpSkillTable[15].push_back(SkillLibrary::VineWhip);
	
}
bool bulbasaur::CanEvolve(Player& player) const { return GetLevel() >= 16; }
shared_ptr<Poketmon> bulbasaur::Evolve() const {
	auto evolved = make_shared<ivysaur>();
	evolved->skillinventory = this->skillinventory;
	return evolved;
}

ivysaur::ivysaur() : Poketmon("이상해풀", 16, 120, "풀", 250, 62, 63, 80, 80, 60) {
	levelUpSkillTable[20].push_back(SkillLibrary::SludgeBomb);
}
bool ivysaur::CanEvolve(Player& player) const { return GetLevel() >= 36; }
shared_ptr<Poketmon> ivysaur::Evolve() const {
	auto evolved = make_shared<venusaur>();
	evolved->skillinventory = this->skillinventory;
	return evolved;
}

venusaur::venusaur() : Poketmon("이상해꽃", 36, 268, "풀", 525, 82, 83, 100, 100, 80) {
	levelUpSkillTable[36].push_back(SkillLibrary::PetalDance);
	levelUpSkillTable[40].push_back(SkillLibrary::SolarBeam);
}

jigglypuff::jigglypuff() : Poketmon("푸린", 5, 120, "노말", 120, 45, 20, 40, 25, 20) {
	skillinventory.AddSkill(SkillLibrary::Growl);
}

meowth::meowth() : Poketmon("나옹", 5, 95, "노말", 40, 45, 35, 40, 40, 90) {
	skillinventory.AddSkill(SkillLibrary::Scratch);
}

psyduck::psyduck() : Poketmon("고라파덕", 5, 100, "물", 50, 52, 48, 65, 50, 55) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
}

machop::machop() : Poketmon("알통몬", 5, 110, "격투", 70, 80, 50, 35, 35, 35) {
	skillinventory.AddSkill(SkillLibrary::Headbutt);
}

gastly::gastly() : Poketmon("고오스", 5, 105, "고스트", 30, 35, 30, 100, 35, 80) {
	skillinventory.AddSkill(SkillLibrary::ShadowMimic);
}

magnemite::magnemite() : Poketmon("코일", 5, 100, "전기", 25, 35, 70, 95, 55, 45) {
	skillinventory.AddSkill(SkillLibrary::ThunderShock);
}

vulpix::vulpix() : Poketmon("식스테일", 5, 90, "불", 38, 41, 40, 50, 65, 65) {
	skillinventory.AddSkill(SkillLibrary::Ember);
}

sandshrew::sandshrew() : Poketmon("모래두지", 5, 100, "땅", 50, 75, 85, 20, 30, 40) {
	skillinventory.AddSkill(SkillLibrary::Rollout);
}

bellsprout::bellsprout() : Poketmon("뚜벅쵸", 5, 85, "풀", 50, 75, 35, 70, 30, 40) {
	skillinventory.AddSkill(SkillLibrary::VineWhip);
	levelUpSkillTable[10].push_back(SkillLibrary::VineWhip);
}

abra::abra() : Poketmon("케이시", 5, 110, "에스퍼", 25, 20, 15, 105, 55, 90) {
	skillinventory.AddSkill(SkillLibrary::Psyshock);
	levelUpSkillTable[10].push_back(SkillLibrary::Psyshock);
}

gyarados::gyarados() : Poketmon("갸라도스", 40, 1000, "물", 150, 125, 79, 60, 100, 81) {
	skillinventory.AddSkill(SkillLibrary::HydroPump);
	skillinventory.AddSkill(SkillLibrary::Bite);
}

alakazam::alakazam() : Poketmon("후딘", 40, 1000, "에스퍼", 120, 50, 45, 135, 95, 120) {
	skillinventory.AddSkill(SkillLibrary::Psybeam);
	skillinventory.AddSkill(SkillLibrary::Psychic);
	levelUpSkillTable[40].push_back(SkillLibrary::Psybeam);
	levelUpSkillTable[40].push_back(SkillLibrary::Psychic);
}

dragonite::dragonite() : Poketmon("망나뇽", 50, 1200, "드래곤", 200, 134, 95, 100, 100, 80) {
	skillinventory.AddSkill(SkillLibrary::DragonClaw);
	skillinventory.AddSkill(SkillLibrary::HyperBeam);
}

arcanine::arcanine() : Poketmon("윈디", 42, 1100, "불", 170, 110, 80, 100, 80, 95) {
	skillinventory.AddSkill(SkillLibrary::Flamethrower);
	skillinventory.AddSkill(SkillLibrary::Bite);
	levelUpSkillTable[42].push_back(SkillLibrary::Flamethrower);
	levelUpSkillTable[42].push_back(SkillLibrary::Bite);
}


golem::golem() : Poketmon("딱구리", 45, 1200, "바위", 180, 120, 130, 55, 65, 45) {
	skillinventory.AddSkill(SkillLibrary::RockSlide);
	skillinventory.AddSkill(SkillLibrary::Earthquake);
}

rattata::rattata() : Poketmon("꼬렛", 5, 90, "노말", 30, 56, 35, 25, 35, 72) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	levelUpSkillTable[10].push_back(SkillLibrary::QuickAttack);
}

zubat::zubat() : Poketmon("주뱃", 6, 95, "비행", 40, 45, 30, 35, 40, 55) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	levelUpSkillTable[8].push_back(SkillLibrary::Growl);
}

ekans::ekans() : Poketmon("아보", 7, 100, "독", 35, 60, 44, 40, 54, 55) {
	skillinventory.AddSkill(SkillLibrary::Bite);
	levelUpSkillTable[10].push_back(SkillLibrary::Growl);
}

geodude::geodude() : Poketmon("꼬마돌", 6, 100, "바위", 40, 80, 100, 30, 30, 20) {
	skillinventory.AddSkill(SkillLibrary::Rollout);
	levelUpSkillTable[9].push_back(SkillLibrary::Tackle);
}

nidoran::nidoran() : Poketmon("니드런", 6, 90, "독", 35, 55, 40, 40, 40, 41) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	levelUpSkillTable[12].push_back(SkillLibrary::Bite);
}

slowpoke::slowpoke() : Poketmon("야돈", 7, 120, "물", 90, 65, 65, 40, 65, 15) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
	levelUpSkillTable[13].push_back(SkillLibrary::Growl);
}

voltorb::voltorb() : Poketmon("찌리리공", 6, 85, "전기", 35, 60, 50, 55, 55, 100) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
	levelUpSkillTable[15].push_back(SkillLibrary::Thunderbolt);
}

cubone::cubone() : Poketmon("탕구리", 7, 100, "땅", 50, 70, 95, 40, 50, 35) {
	skillinventory.AddSkill(SkillLibrary::Headbutt);
	levelUpSkillTable[10].push_back(SkillLibrary::Rollout);
}

tentacool::tentacool() : Poketmon("왕눈해", 6, 95, "물", 40, 40, 35, 50, 100, 70) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
	levelUpSkillTable[14].push_back(SkillLibrary::Tackle);
}

doduo::doduo() : Poketmon("두두", 6, 100, "노말", 35, 85, 45, 35, 35, 75) {
	skillinventory.AddSkill(SkillLibrary::Scratch);
	levelUpSkillTable[12].push_back(SkillLibrary::Growl);
}

ponyta::ponyta() : Poketmon("포니타", 7, 110, "불", 38, 85, 55, 65, 65, 90) {
	skillinventory.AddSkill(SkillLibrary::Ember);
	levelUpSkillTable[13].push_back(SkillLibrary::Tackle);
}

grimer::grimer() : Poketmon("질퍽이", 6, 105, "독", 45, 80, 50, 60, 65, 25) {
	skillinventory.AddSkill(SkillLibrary::SludgeBomb);
	levelUpSkillTable[15].push_back(SkillLibrary::Growl);
}

shellder::shellder() : Poketmon("셀러", 5, 90, "물", 30, 65, 100, 45, 25, 40) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
	levelUpSkillTable[10].push_back(SkillLibrary::Tackle);
}

krabby::krabby() : Poketmon("크랩", 6, 100, "물", 30, 105, 90, 25, 25, 50) {
	skillinventory.AddSkill(SkillLibrary::BubbleBeam);
	levelUpSkillTable[12].push_back(SkillLibrary::Tackle);
}

exeggcute::exeggcute() : Poketmon("아라리", 5, 100, "풀", 60, 40, 80, 60, 45, 40) {
	skillinventory.AddSkill(SkillLibrary::VineWhip);
	levelUpSkillTable[14].push_back(SkillLibrary::Growl);
}

vulpix::vulpix(int level)
	: Poketmon("식스테일", level, 100, "불", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Ember);
}

gastly::gastly(int level)
	: Poketmon("고오스", level, 100, "고스트", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::ShadowMimic);
}

krabby::krabby(int level)
	: Poketmon("크랩", level, 100, "물", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::BubbleBeam);
}

abra::abra(int level)
	: Poketmon("케이시", level, 100, "에스퍼", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Psyshock);
}

magnemite::magnemite(int level)
	: Poketmon("코일", level, 100, "전기", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::ThunderShock);
}

jigglypuff::jigglypuff(int level)
	: Poketmon("푸린", level, 100, "노말", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Growl);
}

machop::machop(int level)
	: Poketmon("알통몬", level, 100, "격투", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Headbutt);
}

bellsprout::bellsprout(int level)
	: Poketmon("뚜벅쵸", level, 100, "풀", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::VineWhip);
}

squirtle::squirtle(int level)
	: Poketmon("꼬부기", level, 100, "물", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
}

bulbasaur::bulbasaur(int level)
	: Poketmon("이상해씨", level, 100, "풀", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::RazorLeaf);
}

charmander::charmander(int level)
	: Poketmon("파이리", level, 100, "불", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Ember);
}

doduo::doduo(int level)
	: Poketmon("두두", level, 100, "노말", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Scratch);
}

geodude::geodude(int level)
	: Poketmon("꼬마돌", level, 100, "바위", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Rollout);
}

rattata::rattata(int level)
	: Poketmon("꼬렛", level, 100, "노말", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
}

voltorb::voltorb(int level)
	: Poketmon("찌리리공", level, 100, "전기", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Thunderbolt);
}

nidoran::nidoran(int level)
	: Poketmon("니드런", level, 100, "독", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
}

slowpoke::slowpoke(int level)
	: Poketmon("야돈", level, 100, "물", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
}

psyduck::psyduck(int level)
	: Poketmon("고라파덕", level, 100, "물", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
}

ponyta::ponyta(int level)
	: Poketmon("포니타", level, 100, "불", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Ember);
}

grimer::grimer(int level)
	: Poketmon("질퍽이", level, 100, "독", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::SludgeBomb);
}

zubat::zubat(int level)
	: Poketmon("주뱃", level, 100, "비행", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Tackle);
}

meowth::meowth(int level)
	: Poketmon("나옹", level, 100, "노말", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Scratch);
}

picachu::picachu(int level)
	: Poketmon("피카츄", level, 100, "전기", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Thunderbolt);
}

ekans::ekans(int level)
	: Poketmon("아보", level, 100, "독", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Bite);
}

shellder::shellder(int level)
	: Poketmon("셀러", level, 100, "물", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::WaterGun);
}

sandshrew::sandshrew(int level)
	: Poketmon("모래두지", level, 100, "땅", 40, 50, 30, 40, 30, 50) {
	skillinventory.AddSkill(SkillLibrary::Rollout);
}

picachu::picachu(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

raichu::raichu(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

squirtle::squirtle(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

wartortle::wartortle(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

blastoise::blastoise(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

charmander::charmander(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

charmeleon::charmeleon(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

charizard::charizard(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

bulbasaur::bulbasaur(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

ivysaur::ivysaur(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

venusaur::venusaur(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

jigglypuff::jigglypuff(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

meowth::meowth(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

psyduck::psyduck(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

machop::machop(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

gastly::gastly(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

magnemite::magnemite(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

vulpix::vulpix(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

sandshrew::sandshrew(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

bellsprout::bellsprout(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

abra::abra(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

gyarados::gyarados(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

alakazam::alakazam(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

dragonite::dragonite(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

arcanine::arcanine(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

golem::golem(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

rattata::rattata(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

zubat::zubat(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

ekans::ekans(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

geodude::geodude(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

nidoran::nidoran(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

slowpoke::slowpoke(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

voltorb::voltorb(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

cubone::cubone(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

tentacool::tentacool(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

doduo::doduo(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

ponyta::ponyta(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

grimer::grimer(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

shellder::shellder(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

krabby::krabby(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}

exeggcute::exeggcute(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd)
	: Poketmon(name, level, exp, type, hp, atk, def, spatk, spdef, spd) {
}