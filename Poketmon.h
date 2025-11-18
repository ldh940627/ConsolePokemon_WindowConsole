#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <map>	
#include "SkillInventory.h"
#include "Skill.h"

class Player;

using namespace std;


class Poketmon
{
protected:
	map<int, vector<shared_ptr<Skill>>> levelUpSkillTable;

private:
	
	string name;
	int level;
	int exp;
	int maxhp;
	int currenthp = maxhp;
	int attack;
	int defense;
	int spattack;
	int spdefense;
	int speed;
	string type;
	int reward = 30;


public:

	SkillInventory skillinventory;

	Poketmon(const string& name, int level, int exp, const string& type, int hp, int atk, int def
		, int spatk, int spdef, int spd);

	int GetLevel() const { return level; }
	int GetExp() const { return exp; }
	int GetMaxHp() const { return maxhp; }
	int GetCurrentHp() const { return currenthp; }
	int GetAttack() const { return attack; }
	int GetDefense() const { return defense; }
	int GetSpAttack() const { return spattack; }
	int GetSpDefense() const { return spdefense; }
	int GetSpeed() const { return speed; }
	string GetType() const { return type; }
	string GetName() const { return name; }
	int Getreward() const { return reward; }

	// setter
	void SetLevel(int l) { level = 1; }
	void SetMaxHp(int hp) { maxhp = hp; }
	void SetCurrentHp(int curhp) { currenthp = curhp; }
	void SetExp(int e) { exp = e; }
	void SetAttack(int atk) { attack = atk; }
	void SetDefense(int def) { defense = def; }
	void SetSpAttack(int spatk) { spattack = spatk; }
	void SetSpDefense(int spdef) { spdefense = spdef; }
	void SetSpeed(int spd) { speed = spd; }


	void GainExp(int amount);
	int RequiredExpForNextLevel() const;
	void levelUp();
	void CheckLearnableSkills();
	void TakeDamage(int amount);
	void Heal(int amount);
	bool IsFainted() const { return currenthp <= 0; }             // »ç¸Á¿©ºÎ
	virtual bool CanEvolve(Player& player) const;
	virtual shared_ptr<Poketmon> Evolve() const;


};




class picachu : public Poketmon {
public:

	picachu();
	picachu(int level);
	picachu(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class raichu : public Poketmon {
public:
	raichu();
	raichu(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

};

class squirtle : public Poketmon {
public:
	squirtle();
	squirtle(int level);
	squirtle(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class wartortle : public Poketmon {
public:
	wartortle();
	wartortle(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class charmander : public Poketmon {
public:
	charmander();
	charmander(int level);
	charmander(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class charmeleon : public Poketmon {
public:
	charmeleon();
	charmeleon(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class bulbasaur : public Poketmon {
public:
	bulbasaur();
	bulbasaur(int level);
	bulbasaur(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class ivysaur : public Poketmon {
public:
	ivysaur();
	ivysaur(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);

	bool CanEvolve(Player& player) const override;
	shared_ptr<Poketmon> Evolve() const override;
};

class jigglypuff : public Poketmon {
public:
	jigglypuff();
	jigglypuff(int level);
	jigglypuff(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class meowth : public Poketmon {
public:
	meowth();
	meowth(int level);
	meowth(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class psyduck : public Poketmon {
public:
	psyduck();
	psyduck(int level);
	psyduck(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class machop : public Poketmon {
public:
	machop();
	machop(int level);
	machop(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class gastly : public Poketmon {
public:
	gastly();
	gastly(int level);
	gastly(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class magnemite : public Poketmon {
public:
	magnemite();
	magnemite(int level);
	magnemite(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class vulpix : public Poketmon {
public:
	vulpix();
	vulpix(int level);
	vulpix(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class sandshrew : public Poketmon {
public:
	sandshrew();
	sandshrew(int level);
	sandshrew(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class bellsprout : public Poketmon {
public:
	bellsprout();
	bellsprout(int level);
	bellsprout(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class abra : public Poketmon {
public:
	abra();
	abra(int level);
	abra(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class gyarados : public Poketmon {
public:
	gyarados();
	gyarados(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class alakazam : public Poketmon {
public:
	alakazam();
	alakazam(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class dragonite : public Poketmon {
public:
	dragonite();
	dragonite(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class arcanine : public Poketmon {
public:
	arcanine();
	arcanine(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class venusaur : public Poketmon {
public:
	venusaur();
	venusaur(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class golem : public Poketmon {
public:
	golem();
	golem(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class blastoise : public Poketmon {
public:
	blastoise();
	blastoise(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class charizard : public Poketmon {
public:
	charizard();
	charizard(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class rattata : public Poketmon {
public:
	rattata();
	rattata(int level);
	rattata(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class zubat : public Poketmon {
public:
	zubat();
	zubat(int level);
	zubat(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class ekans : public Poketmon {
public:
	ekans();
	ekans(int level);
	ekans(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class geodude : public Poketmon {
public:
	geodude();
	geodude(int level);
	geodude(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class nidoran : public Poketmon {
public:
	nidoran();
	nidoran(int level);
	nidoran(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class slowpoke : public Poketmon {
public:
	slowpoke();
	slowpoke(int level);
	slowpoke(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class voltorb : public Poketmon {
public:
	voltorb();
	voltorb(int level);
	voltorb(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class cubone : public Poketmon {
public:
	cubone();
	cubone(int level);
	cubone(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class tentacool : public Poketmon {
public:
	tentacool();
	tentacool(int level);
	tentacool(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class doduo : public Poketmon {
public:
	doduo();
	doduo(int level);
	doduo(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class ponyta : public Poketmon {
public:
	ponyta();
	ponyta(int level);
	ponyta(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class grimer : public Poketmon {
public:
	grimer();
	grimer(int level);
	grimer(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class shellder : public Poketmon {
public:
	shellder();
	shellder(int level);
	shellder(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class krabby : public Poketmon {
public:
	krabby();
	krabby(int level);
	krabby(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};

class exeggcute : public Poketmon {
public:
	exeggcute();
	exeggcute(int level);
	exeggcute(string name, int level, int exp, string type, int hp, int atk, int def, int spatk, int spdef, int spd);
};