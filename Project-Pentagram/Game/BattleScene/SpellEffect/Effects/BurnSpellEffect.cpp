#include "BurnSpellEffect.h"
#include <Game/BattleScene/SpellCaster/CasterController.h>

void BurnSpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    CasterController* caster = va_arg(args, CasterController*);
    caster->TakeDamage(m_EffectStack);

    std::cout << "\tBURN STACK: " << m_EffectStack << "\n";

    m_EffectStack--;
    if (m_EffectStack == 0)
    {
        ResetEffect();
    }
};
