#pragma once
#include "ChannelEffectType.h"

const std::string ChannelEffectType::enum_string[] = {
    "None",
    "Wait",
    "Active"
};

ChannelEffectEnum ChannelEffectType::GetEnum(std::string typeString)
{
    for (int i = 0; i < 3; i++)
    {
        if (typeString.compare(enum_string[i]) == 0) return ChannelEffectEnum(i);
    }
    return ChannelEffectEnum::None;
}
