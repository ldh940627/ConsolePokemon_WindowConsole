#include "Skill.h"
#include "Poketmon.h"
#include "TypeEffectiveness.h"
#include "UIManager.h"

Skill::Skill(string name, int power, string type)
	: name(name), power(power), type(type) {
}

NormalAttackSkill::NormalAttackSkill(string name, int power, string type)
	: Skill(name, power, type) {
}

void NormalAttackSkill::Use(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target)
{
	int levelFactor = (user->GetLevel() * 2 / 5 + 2);
	float damage = (power * user->GetAttack() * levelFactor) / target->GetDefense() / 50.0f + 2;

	// 상성 적용
	float multiplier = GetTypeEffectiveness(this->GetType(), target->GetType());
	damage *= multiplier;

	if (damage < 1) damage = 1;
	target->TakeDamage(static_cast<int>(damage));

	UIManager::GetInstance();

	// 상성 메시지 출력
	if (multiplier > 1.0f)
		UIManager::GetInstance().AddBattleLog("효과가 굉장했다!");
	else if (multiplier < 1.0f && multiplier > 0.0f)
		UIManager::GetInstance().AddBattleLog("효과가 별로였다...");
	else if (multiplier == 0.0f)
		UIManager::GetInstance().AddBattleLog("전혀 효과가 없었다!");
}

SpecialAttackSkill::SpecialAttackSkill(string name, int power, string type)
	: Skill(name, power, type) {
}

void SpecialAttackSkill::Use(shared_ptr<Poketmon> user, shared_ptr<Poketmon> target)
{
	int levelFactor = (user->GetLevel() * 2 / 5 + 2);
	int damage = (power * user->GetSpAttack() * levelFactor) / target->GetSpDefense() / 50 + 2;
	
	// 상성 적용
	float multiplier = GetTypeEffectiveness(this->GetType(), target->GetType());
	damage *= multiplier;

	if (damage < 1) damage = 1;
	target->TakeDamage(static_cast<int>(damage));

	UIManager::GetInstance();

	// 상성 메시지 출력
	if (multiplier > 1.0f)
		UIManager::GetInstance().AddBattleLog("효과가 굉장했다!");
	else if (multiplier < 1.0f && multiplier > 0.0f)
		UIManager::GetInstance().AddBattleLog("효과가 별로였다...");
	else if (multiplier == 0.0f)
		UIManager::GetInstance().AddBattleLog("전혀 효과가 없었다!");
	
	
}
