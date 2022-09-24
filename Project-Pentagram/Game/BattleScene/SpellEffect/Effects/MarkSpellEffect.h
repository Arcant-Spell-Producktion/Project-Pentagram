#pragma once
#include "BaseSpellEffect.h"

class MarkSpellEffect :public BaseSpellEffect
{
private:
    const int damageMultiplier = 2;

public:
    MarkSpellEffect() :BaseSpellEffect(SpellEffectEnum::Mark,EffectResolveType::OnDamageCalculation)
    {
        m_IsEffectApplyByChance = true;
        m_IsEffectActiveOnce = true;
    }

    virtual void ResolveEffect(std::va_list args) override
    {
        if (!m_IsEffectActive) return;

        int* damage = va_arg(args, int*);

        (*damage) *= damageMultiplier;

        va_end(args);

        ResetEffect();
    };
};