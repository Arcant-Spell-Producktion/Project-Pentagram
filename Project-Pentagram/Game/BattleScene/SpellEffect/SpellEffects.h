﻿#pragma once
#include <vector>
#include "Effects/BaseSpellEffect.h"

class BurnSpellEffect :public BaseSpellEffect
{
private:
    const int BurnDamagePerStack = 10;

public:
    BurnSpellEffect() :BaseSpellEffect(SpellEffectEnum::Burn, EffectResolveType::OnStartTurn)
    {
        m_IsEffectStack = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};

class MarkSpellEffect :public BaseSpellEffect
{
private:
    const int m_DamageMultiplier = 2;

public:
    MarkSpellEffect() :BaseSpellEffect(SpellEffectEnum::Mark, EffectResolveType::OnDamageCalculation)
    {
        m_IsEffectActiveOnce = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};

class OverflowSpellEffect :public BaseSpellEffect
{
private:

public:
    OverflowSpellEffect() :BaseSpellEffect(SpellEffectEnum::Overflow, EffectResolveType::OnStartTurn)
    {
        m_EffectStackLimit = 5;
        m_IsEffectStack = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};

class FreezeSpellEffect :public BaseSpellEffect
{
private:

public:
    FreezeSpellEffect() :BaseSpellEffect(SpellEffectEnum::Freeze, EffectResolveType::OnStartTurn)
    {
        m_EffectStackLimit = 3;
        m_IsEffectStack = true;
        m_IsEffectResetOnEndOfCastPhase = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};

class FortifySpellEffect :public BaseSpellEffect
{

public:
    FortifySpellEffect() :BaseSpellEffect(SpellEffectEnum::Fortify, EffectResolveType::OnDamageCalculation)
    {
        m_EffectStackLimit = 3;
        m_IsEffectStack = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};

class PetrifySpellEffect :public BaseSpellEffect
{
private:
public:
    PetrifySpellEffect() :BaseSpellEffect(SpellEffectEnum::Petrify, EffectResolveType::OnStartTurn)
    {
        m_EffectStackLimit = 3;
        m_IsEffectStack = true;
        m_IsEffectActiveOnce = true;
        m_IsEffectResetOnEndOfCastPhase = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
    
};

class BoostSpellEffect :public BaseSpellEffect
{
private:
    int m_WillBuff = 1;
    int m_TimeBuff = 1;
    int m_DmgBuff = 10;

public:
    BoostSpellEffect() :BaseSpellEffect(SpellEffectEnum::Boost, EffectResolveType::OnStartTurn)
    {
        m_EffectStackLimit = 8;
        m_IsEffectStack = true;
        m_IsEffectResetAtStackLimit = true;
    }

    virtual void ResolveEffect(std::va_list args) override;
};

class SpellEffects
{
public:
    static std::vector<BaseSpellEffect*> GetSpellEffects()
    {
        std::vector<BaseSpellEffect*> effects =
        {
            new BurnSpellEffect(),
            new MarkSpellEffect(),
            new OverflowSpellEffect(),
            new FreezeSpellEffect(),
            new FortifySpellEffect(),
            new PetrifySpellEffect(),
            new BoostSpellEffect(),
        };

        return effects;
    }
};