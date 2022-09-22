#pragma once
#include "BaseSpellEffect.h"
#include "Game/Spells/SpellEffectType.h"

class SpellEffectFactory
{
public:
    static BaseSpellEffect* CreateSpellEffect(SpellEffectType::Type type) {}
};