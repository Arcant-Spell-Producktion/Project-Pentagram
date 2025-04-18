#pragma once
#include <string>

enum class SpellTargetEnum
{
    Opponent = 0,
    Self = 1,
};

class SpellTargetType
{
private:
    static const std::string enum_string[];
public:
    static SpellTargetEnum GetEnum(std::string typeString);

    static std::string GetString(SpellTargetEnum type) { return enum_string[(int)type]; }
};