#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Poketmon;


class Skill
{
protected:
	string name;
	int power;
	string type;

public:
	Skill(string name, int power, string type);

	virtual ~Skill() = default;

	virtual void Use(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target) = 0;

	string GetName() const { return name; }
	string GetType() const { return type; }
	int GetPower() const { return power; }
};

class NormalAttackSkill : public Skill
{
public:
	NormalAttackSkill(string name, int power, string type);

	void Use(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target) override;
};

class SpecialAttackSkill : public Skill
{
public:
	SpecialAttackSkill(string name, int power, string type);

	void Use(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target) override;
};
