#pragma once
#include <memory>

class Skill;

using namespace std;

namespace SkillLibrary {
    
    // 노말 스킬
    extern shared_ptr<Skill> Tackle;
    extern shared_ptr<Skill> Scratch;
    extern shared_ptr<Skill> Headbutt;
    extern shared_ptr<Skill> Rollout;
    extern shared_ptr<Skill> Growl;
    extern shared_ptr<Skill> Bite;
    extern shared_ptr<Skill> SludgeBomb;
    extern shared_ptr<Skill> QuickAttack;


    // 특수 스킬
    extern shared_ptr<Skill> Thunderbolt;
    extern shared_ptr<Skill> WaterGun;
    extern shared_ptr<Skill> Ember;
    extern shared_ptr<Skill> VineWhip;
    extern shared_ptr<Skill> Psyshock;
    extern shared_ptr<Skill> ShadowMimic;
    extern shared_ptr<Skill> ThunderShock;
    extern shared_ptr<Skill> Thunder;
    extern shared_ptr<Skill> BubbleBeam;
    extern shared_ptr<Skill> Flamethrower;
    extern shared_ptr<Skill> RazorLeaf;
    extern shared_ptr<Skill> HydroPump;
    extern shared_ptr<Skill> Psybeam;
    extern shared_ptr<Skill> Psychic;
    extern shared_ptr<Skill> DragonClaw;
    extern shared_ptr<Skill> HyperBeam;
    extern shared_ptr<Skill> SolarBeam;
    extern shared_ptr<Skill> RockSlide;
    extern shared_ptr<Skill> Earthquake;
    extern shared_ptr<Skill> WaterCannon;
    extern shared_ptr<Skill> FlareBlitz;
    extern shared_ptr<Skill> WingAttack;
    extern shared_ptr<Skill> HeatWave;
    extern shared_ptr<Skill> PetalDance;
}
