#include "SkillInventory.h"
#include "Skill.h"


bool SkillInventory::AddSkill(shared_ptr<Skill> skill)
{
	if (skills.size() >= MAX_SKILLS)
	{
		cout << "스킬은 최대 4개까지만 보유할 수 있습니다!" << endl;
		return false;
	}
	skills.push_back(skill);
	return true;
}

bool SkillInventory::IsFull() const
{
	return skills.size() >= MAX_SKILLS;
}

void SkillInventory::ReplaceSkill(int index, shared_ptr<Skill> newSkill)
{
	if (index >= 0 && index < skills.size())
	{
		skills[index] = newSkill;
		cout << "스킬이 " << newSkill->GetName() << "으로 교체되었습니다!" << endl;
	}
	else {
		cout << "잘못된 스킬 번호입니다!" << endl;
	}
}

const vector<shared_ptr<Skill>>& SkillInventory::GetSkills() const
{
	return skills;
}

void SkillInventory::DisplaySkillInventory() const
{
	cout << "[스킬목록]" << endl;
	for (int i = 0; i < skills.size(); ++i)
	{
		cout << i + 1 << ". " << skills[i]->GetName() << " (" << skills[i]->GetType() << ", 위력: " << skills[i]->GetPower() << ")" << endl;
	}
}

shared_ptr<Skill> SkillInventory::GetSkill(int index) const
{
	if (index < 0 || index >= skills.size()) return nullptr;
	return skills[index];
}

int SkillInventory::GetSkillCount() const
{
	return skills.size();
}
