#pragma once
#include <map>
#include "Game/BattleScene/SpellEffect/SpellEffects.h"

class CasterEffectManager
{
private:
    std::map<SpellEffectEnum,BaseSpellEffect*> m_Effects;
public:
    Event<SpellEffectEnum> OnEffectApply;
    Event<SpellEffectEnum> OnEffectResolve;
    Event<SpellEffectEnum> OnEffectReset;

    Event<std::vector<EffectDetail_T>&> OnEffectUpdate;

    CasterEffectManager()
    {
        for (auto effect: SpellEffects::GetSpellEffects())
        {
            effect->OnEffectApply = [this](SpellEffectEnum type) { OnEffectApply.Invoke(type); };
            effect->OnEffectResolve = [this](SpellEffectEnum type) { OnEffectResolve.Invoke(type); };
            effect->OnEffectReset = [this](SpellEffectEnum type) { OnEffectReset.Invoke(type); };

            m_Effects.emplace(effect->GetEffectType(),effect);
        }
    }

    void UpdateSpellEvent()
    {
        std::vector<EffectDetail_T> effects;

        for (auto effPair: m_Effects)
            effects.push_back({ effPair.first ,effPair.second->GetStackCount() });

        OnEffectUpdate.Invoke(effects);
    }

    void AppliedEffect(SpellEffectEnum type, int value)
    {
        m_Effects[type]->AppliedEffect(value);
        UpdateSpellEvent();
    }

    void ResolveEffect(EffectResolveType resolveType, int argc = 0, ...)
    {
        std::va_list args;
        va_start(args, argc);

        for (auto effectPair : m_Effects)
        {
            auto effect = effectPair.second;
            if (effect->GetResolveType() == resolveType)
            {
                std::va_list temp;
                va_copy(temp, args);
                effect->ResolveEffect(temp);
                va_end(temp);
            }
            
        }

        va_end(args);
        UpdateSpellEvent();
    }

    void OnCastPhaseEnd()
    {
        for (auto effectPair : m_Effects)
        {
            auto effect = effectPair.second;
            effect->OnCastPhaseEnd();
        }
        UpdateSpellEvent();
    }

    void OnEndRound()
    {
        for (auto effectPair : m_Effects)
        {
            auto effect = effectPair.second;
            effect->OnEndRound();
        }
        UpdateSpellEvent();
    }

    ~CasterEffectManager()
    {
        for (auto effectPair : m_Effects)
        {
            delete effectPair.second;
        }
        m_Effects.clear();
    }
};