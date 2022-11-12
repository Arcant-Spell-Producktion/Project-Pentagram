#include "SpellEffectType.h"

const std::string SpellEffectType::enum_string[] = {
    "None",
    "Mark",
    "Burn",
    "Overflow",
    "Freeze",
};

SpellEffectEnum SpellEffectType::GetEnum(std::string typeString)
{
    for (int i = 0; i < sizeof(enum_string)/sizeof(enum_string[0]); i++)
    {
        if (typeString.compare(enum_string[i]) == 0) return SpellEffectEnum(i);
    }
    return SpellEffectEnum::None;
}

bool SpellEffectType::IsEffectTargetEnemy(SpellEffectEnum type)
{
    switch (type)
    {
    case SpellEffectEnum::None:
    case SpellEffectEnum::Mark:
    case SpellEffectEnum::Burn:
    case SpellEffectEnum::Freeze:
        return true;
    case SpellEffectEnum::Overflow:
        return false;
    }
}
