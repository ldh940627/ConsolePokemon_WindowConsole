#pragma once
#include <string>
#include <map>
using namespace std;

static map<string, map<string, float>> typeEffectiveness = {
    { "불꽃",   { {"풀", 2.0f}, {"얼음", 2.0f}, {"벌레", 2.0f}, {"불꽃", 0.5f}, {"물", 0.5f}, {"바위", 0.5f} } },
    { "물",     { {"불꽃", 2.0f}, {"바위", 2.0f}, {"땅", 2.0f}, {"물", 0.5f}, {"풀", 0.5f} } },
    { "풀",     { {"물", 2.0f}, {"바위", 2.0f}, {"땅", 2.0f}, {"불꽃", 0.5f}, {"풀", 0.5f} } },
    { "전기",   { {"물", 2.0f}, {"비행", 2.0f}, {"전기", 0.5f}, {"땅", 0.0f} } },
    { "노말",   { {"바위", 0.5f}, {"고스트", 0.0f} } },
    { "격투",   { {"노말", 2.0f}, {"바위", 2.0f}, {"얼음", 2.0f}, {"고스트", 0.0f} } },
    { "에스퍼", { {"격투", 2.0f}, {"독", 2.0f}, {"에스퍼", 0.5f} } },
    { "바위",   { {"불꽃", 2.0f}, {"얼음", 2.0f}, {"비행", 2.0f}, {"벌레", 2.0f} } },
    { "땅",     { {"불꽃", 2.0f}, {"전기", 2.0f}, {"독", 2.0f}, {"바위", 2.0f}, {"비행", 0.0f} } },
    { "고스트", { {"고스트", 2.0f}, {"노말", 0.0f} } },
    { "비행",   { {"풀", 2.0f}, {"격투", 2.0f}, {"벌레", 2.0f} } },
    { "얼음",   { {"풀", 2.0f}, {"비행", 2.0f}, {"땅", 2.0f}, {"불꽃", 0.5f}, {"물", 0.5f} } },
    { "독",     { {"풀", 2.0f}, {"독", 0.5f}, {"땅", 0.5f}, {"바위", 0.5f} } }
};

inline float GetTypeEffectiveness(const string& attackType, const string& targetType) {
    if (typeEffectiveness.count(attackType) && typeEffectiveness[attackType].count(targetType))
        return typeEffectiveness[attackType][targetType];
    return 1.0f;
}

