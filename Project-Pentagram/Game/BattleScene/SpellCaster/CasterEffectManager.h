#pragma once
#include <map>
#include "Game/BattleScene/SpellEffect/SpellEffects.h"

class CasterEffectManager
{
private:
    std::map<SpellEffectEnum,BaseSpellEffect*> m_Effects;
public:
    CasterEffectManager()
    {
        for (auto effect: SpellEffects::GetSpellEffects())
        {
            m_Effects.emplace(effect->GetEffectType(),effect);
        }
    }

    void AppliedEffect(SpellEffectEnum type, int value)
    {
        m_Effects[type]->AppliedEffect(value);
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