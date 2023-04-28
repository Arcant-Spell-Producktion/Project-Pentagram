#pragma once
#include <string>

enum class SpellEffectEnum
{
    None = 0,
    Mark,
    Burn,
    Overflow,
    Freeze,
    Fortify,
    Petrify,
    Boost,
    BoostTime,
    BoostWill,
    BoostDmg,
};

struct EffectDetail_T
{
    SpellEffectEnum EffectType;
    int Stack;

    EffectDetail_T(SpellEffectEnum type, int n) :EffectType(type), Stack(n) {};
};

class SpellEffectType
{
private:
    static const std::string enum_string[];
public:
    static SpellEffectEnum GetEnum(std::string typeString);
    
    static std::string GetString(SpellEffectEnum type) { return enum_string[(int)type]; }

    static bool IsEffectApplyByChance(SpellEffectEnum type);

    static bool IsEffectTargetEnemy(SpellEffectEnum type);
};
