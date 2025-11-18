#include "SkillLibrary.h"
#include "Skill.h"


// 노말 스킬
shared_ptr<Skill> SkillLibrary::Tackle = make_shared<NormalAttackSkill>("몸통박치기", 40, "노말");
shared_ptr<Skill> SkillLibrary::Scratch = make_shared<NormalAttackSkill>("할퀴기", 40, "노말");
shared_ptr<Skill> SkillLibrary::Headbutt = make_shared<NormalAttackSkill>("박치기", 60, "격투");
shared_ptr<Skill> SkillLibrary::Rollout = make_shared<NormalAttackSkill>("구르기", 30, "노말");
shared_ptr<Skill> SkillLibrary::Growl = make_shared<SpecialAttackSkill>("울음소리", 0, "노말");
shared_ptr<Skill> SkillLibrary::Bite = make_shared<NormalAttackSkill>("깨물기", 60, "노말");
shared_ptr<Skill> SkillLibrary::SludgeBomb = make_shared<SpecialAttackSkill>("오물폭탄", 90, "풀");
shared_ptr<Skill> SkillLibrary::QuickAttack = make_shared<NormalAttackSkill>("전광석화", 60, "노말");

// 특수 스킬
shared_ptr<Skill> SkillLibrary::Thunderbolt = make_shared<SpecialAttackSkill>("10만볼트", 90, "전기");
shared_ptr<Skill> SkillLibrary::WaterGun = make_shared<SpecialAttackSkill>("물대포", 40, "물");
shared_ptr<Skill> SkillLibrary::Ember = make_shared<SpecialAttackSkill>("불꽃세례", 40, "불");
shared_ptr<Skill> SkillLibrary::VineWhip = make_shared<SpecialAttackSkill>("덩굴채찍", 45, "풀");
shared_ptr<Skill> SkillLibrary::Psyshock = make_shared<SpecialAttackSkill>("사이코쇼크", 80, "에스퍼");
shared_ptr<Skill> SkillLibrary::ShadowMimic = make_shared<SpecialAttackSkill>("그림자흉내", 70, "고스트");
shared_ptr<Skill> SkillLibrary::ThunderShock = make_shared<SpecialAttackSkill>("전기쇼크", 40, "전기");
shared_ptr<Skill> SkillLibrary::Thunder = make_shared<SpecialAttackSkill>("번개", 110, "전기");
shared_ptr<Skill> SkillLibrary::BubbleBeam = make_shared<SpecialAttackSkill>("거품광선", 65, "물");
shared_ptr<Skill> SkillLibrary::Flamethrower = make_shared<SpecialAttackSkill>("화염방사", 90, "불");
shared_ptr<Skill> SkillLibrary::RazorLeaf = make_shared<SpecialAttackSkill>("잎날가르기", 55, "풀");
shared_ptr<Skill> SkillLibrary::HydroPump = make_shared<SpecialAttackSkill>("하이드로펌프", 110, "물");
shared_ptr<Skill> SkillLibrary::Psybeam = make_shared<SpecialAttackSkill>("사이코빔", 65, "에스퍼");
shared_ptr<Skill> SkillLibrary::Psychic = make_shared<SpecialAttackSkill>("사이코키네시스", 90, "에스퍼");
shared_ptr<Skill> SkillLibrary::DragonClaw = make_shared<SpecialAttackSkill>("드래곤크루", 80, "드래곤");
shared_ptr<Skill> SkillLibrary::HyperBeam = make_shared<SpecialAttackSkill>("파괴광선", 150, "노말");
shared_ptr<Skill> SkillLibrary::SolarBeam = make_shared<SpecialAttackSkill>("솔라빔", 120, "풀");
shared_ptr<Skill> SkillLibrary::RockSlide = make_shared<NormalAttackSkill>("암석봉인", 75, "바위");
shared_ptr<Skill> SkillLibrary::Earthquake = make_shared<NormalAttackSkill>("지진", 100, "땅");
shared_ptr<Skill> SkillLibrary::WaterCannon = make_shared<SpecialAttackSkill>("물대포", 100, "물");
shared_ptr<Skill> SkillLibrary::FlareBlitz = make_shared<SpecialAttackSkill>("플레어드라이브", 100, "불");
shared_ptr<Skill> SkillLibrary::WingAttack = make_shared<SpecialAttackSkill>("날개치기", 60, "비행");
shared_ptr<Skill> SkillLibrary::HeatWave = make_shared<SpecialAttackSkill>("열풍", 80, "불");
shared_ptr<Skill> SkillLibrary::PetalDance = make_shared<SpecialAttackSkill>("꽃잎댄스", 80, "풀");