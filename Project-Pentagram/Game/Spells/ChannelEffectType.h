#pragma once
#include <string>

enum class ChannelEffectEnum
{
    None = 0,
    Wait = 1,
    Active = 2,
    Trap = 3,
    Counter = 4,
};

class ChannelEffectType
{
private:
    static const std::string enum_string[];
public:
    static ChannelEffectEnum GetEnum(std::string typeString);

    static std::string GetString(ChannelEffectEnum type) { return enum_string[(int)type]; }
};