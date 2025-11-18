#pragma once
#include <iostream>
#include <vector>
#include <memory>

class Skill;


using namespace std;


class SkillInventory
{
private:
	vector<shared_ptr<Skill>> skills;
	static const int MAX_SKILLS = 4;

public:

	// Getter
	const vector<shared_ptr<Skill>>& GetSkills() const;  // 백터형
	shared_ptr<Skill> GetSkill(int index) const;         // 포인터형
	int GetSkillCount() const;                           // 백터 사이즈

	bool AddSkill(shared_ptr<Skill> skill);
	bool IsFull() const;
	void ReplaceSkill(int index, shared_ptr<Skill> newSkill);
	void DisplaySkillInventory() const;
	
	
};

