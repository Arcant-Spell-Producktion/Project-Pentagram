#pragma once
#include <string>

enum class SpellEffectEnum
{
    None = 0,
    Mark,
    Burn
};

class SpellEffectType
{
private:
    static const std::string enum_string[];
public:
    static SpellEffectEnum GetEnum(std::string typeString);

    static std::string GetString(SpellEffectEnum type) { return enum_string[(int)type]; }
};
