#include <Game/BattleScene/SpellCaster/CasterController.h>

void BurnSpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    OnEffectResolve.Invoke(m_EffectType);

    CasterController* caster = va_arg(args, CasterController*);
    caster->TakeDamage(m_EffectStack * BurnDamagePerStack);

    std::cout << "\tBURN STACK: " << m_EffectStack << "\n";

    m_EffectStack--;
    if (m_EffectStack == 0)
    {
        ResetEffect();
    }
};

void MarkSpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    int* damage = va_arg(args, int*);

    (*damage) *= m_DamageMultiplier;

    va_end(args);

    ResetEffect();
};

void OverflowSpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    CasterController* caster = va_arg(args, CasterController*);
    caster->GetCasterManager()->ChangeMana(m_EffectStack);
}

void FreezeSpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    CasterController* caster = va_arg(args, CasterController*);
    caster->GetCasterManager()->SetTimeDebuff(m_EffectStack);
}

void FortifySpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    int* damage = va_arg(args, int*);

    (*damage) = 0;

    va_end(args);

    m_EffectStack--;
    if (m_EffectStack == 0)
    {
        ResetEffect();
    }
}

void PetrifySpellEffect::ResolveEffect(std::va_list args)
{
    if (!m_IsEffectActive) return;

    CasterController* caster = va_arg(args, CasterController*);
    caster->GetCasterManager()->SetWillDebuff(m_EffectStack);
}

void BoostSpellEffect::ResolveEffect(std::va_list args)
{
    std::cout << "BoostSpellEffect::ResolveEffect\n";

    if (!m_IsEffectActive) return;

    std::cout << "BoostSpellEffect::ACTIVE\n";

    CasterController* cc = va_arg(args, CasterController*);
    CasterManager* cm =cc->GetCasterManager();
    std::cout << "BoostSpellEffect::CC " << cc << "\n";

    if (m_EffectStack >= 2)
    {
        std::cout << "BoostSpellEffect::TIME BUFF\n";

        cm->SetTimeBuff(m_TimeBuff);
    }

    if (m_EffectStack >= 5)
    {
        std::cout << "BoostSpellEffect::WILL BUFF\n";

        cm->SetWillBuff(m_WillBuff);
    }

    if (m_EffectStack >= 8)
    {
        std::cout << "BoostSpellEffect::DMG BUFF\n";

        cm->SetDmgBuff(m_DmgBuff);
    }

}
