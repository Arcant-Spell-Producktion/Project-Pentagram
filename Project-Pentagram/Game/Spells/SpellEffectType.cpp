#include "SpellEffectType.h"

const std::string SpellEffectType::enum_string[] = {
    "None",
    "Mark",
    "Burn",
    "Overflow",
    "Freeze",
    "Fortify",
    "Petrify"
};

SpellEffectEnum SpellEffectType::GetEnum(std::string typeString)
{
    for (int i = 0; i < sizeof(enum_string)/sizeof(enum_string[0]); i++)
    {
        if (typeString.compare(enum_string[i]) == 0) return SpellEffectEnum(i);
    }
    return SpellEffectEnum::None;
}

bool SpellEffectType::IsEffectApplyByChance(SpellEffectEnum type)
{
    switch (type)
    {
    case SpellEffectEnum::None:
    case SpellEffectEnum::Mark:
        return true;
    case SpellEffectEnum::Burn:
        return false;
    case SpellEffectEnum::Freeze:
    case SpellEffectEnum::Overflow:
    case SpellEffectEnum::Fortify:
    case SpellEffectEnum::Petrify:
        return true;
    }
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
    case SpellEffectEnum::Fortify:
    case SpellEffectEnum::Petrify:
        return true;
    }
}
