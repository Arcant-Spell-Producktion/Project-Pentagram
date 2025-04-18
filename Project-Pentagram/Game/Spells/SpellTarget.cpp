#include "SpellTarget.h"

#include "ChannelEffectType.h"

const std::string SpellTargetType::enum_string[] = {
    "Opponent",
    "Self"
};

SpellTargetEnum SpellTargetType::GetEnum(std::string typeString)
{
    for (int i = 0; i < 2; i++)
    {
        if (typeString.compare(enum_string[i]) == 0) return SpellTargetEnum(i);
    }
    return SpellTargetEnum::Opponent;
}
