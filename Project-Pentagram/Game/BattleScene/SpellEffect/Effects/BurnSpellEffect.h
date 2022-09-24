#pragma once
#include "BaseSpellEffect.h"

class BurnSpellEffect :public BaseSpellEffect
{
private:
    const int damageMultiplier = 2;

public:
    BurnSpellEffect() :BaseSpellEffect(SpellEffectEnum::Burn,EffectResolveType::OnStartTurn)
    {
        m_IsEffectStack = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};