#pragma once
#include <cstdlib>
#include <cstdarg>
#include "Game/Spells/SpellEffectType.h"

enum class EffectResolveType
{
    None = -1,
    OnStartTurn = 0,
    OnDamageCalculation,
};

class BaseSpellEffect
{
protected:
    //Effect Data
    SpellEffectEnum m_EffectType;
    EffectResolveType m_ResolveType;
    bool m_IsEffectActive = false;
    int m_EffectStack = 0;
    int m_EffectStackLimit = 99;

    //Effect Setting
    bool m_IsEffectApplyByChance = false;
    bool m_IsEffectStack = false;
    bool m_IsEffectActiveOnce = false;
    bool m_IsEffectStackDecreaseOnEndRound = false;
    bool m_IsEffectResetOnEndOfCastPhase = false;

public:
    BaseSpellEffect(SpellEffectEnum effectType, EffectResolveType resolveType) :
        m_EffectType(effectType), m_ResolveType(resolveType)
    {
        m_IsEffectApplyByChance = SpellEffectType::IsEffectApplyByChance(effectType);
    }

    SpellEffectEnum GetEffectType() { return m_EffectType; }
    EffectResolveType GetResolveType() { return m_ResolveType; }
    int GetStackCount() { return m_EffectStack; }

    virtual void ResolveEffect(std::va_list args) = 0;

    virtual void AppliedEffect(int value, int stack = 1)
    {

        if (m_IsEffectApplyByChance)
        {
            int nRandom = rand() % 100;
            printf("Value: %d ? Rand: %d , result %d\n", value, nRandom, nRandom <= value);
            if (nRandom > value) return;
        }
        else
        {
            stack = value;
        }

        if (m_IsEffectStack)
        {
            m_EffectStack += stack;
            if (m_EffectStack >= m_EffectStackLimit) m_EffectStack = m_EffectStackLimit;
        }
        else
        {
            m_EffectStack = stack;
        }
        printf("Stack: %d\n", m_EffectStack);

        m_IsEffectActive = true;
    }

    void OnCastPhaseEnd()
    {
        if (m_IsEffectResetOnEndOfCastPhase) { ResetEffect(); }
    }

    void OnEndRound()
    {
        if (m_IsEffectStackDecreaseOnEndRound) m_EffectStack -= 1;
        if (m_IsEffectActiveOnce) { m_IsEffectStack = 0; }
        if (m_IsEffectStack == 0) ResetEffect();
    }

    void ResetEffect()
    {
        m_IsEffectActive = false;
        m_EffectStack = 0;
    }
};