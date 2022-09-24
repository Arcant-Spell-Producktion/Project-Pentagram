#pragma once
#include <vector>
#include "Effects/MarkSpellEffect.h"
#include "Effects/BurnSpellEffect.h"

class SpellEffects
{
public:
    static std::vector<BaseSpellEffect*> GetSpellEffects()
    {
        std::vector<BaseSpellEffect*> effects =
        {
            new MarkSpellEffect(),
            new BurnSpellEffect()
        };

        return effects;
    }
};