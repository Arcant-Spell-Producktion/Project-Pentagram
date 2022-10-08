#include "ResolveBattleState.h"
#include <Game/BattleScene/BattleManager.h>


BattleManager* m_ResolveBattleManager = nullptr;

void ResolveBattleState::ResolveTrack()
{
    std::cout << "Resovel Track: " << m_TrackResolveIndex << "\n";

    m_CurrentTrack = m_ResolveBattleManager->Data.Timeline.GetTimetrack(m_TrackResolveIndex);
    std::cout << "\tGet Track: " << m_TrackResolveIndex << "\n";
    std::cout << "\tTrack Size: " << m_CurrentTrack->GetSpellList().size() << "\n";

    CasterPosition casterPosition = m_CurrentTrack->GetWillCompareResult();
    CasterPosition targetPosition = casterPosition == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;
    std::cout << "\tGet casterToResolve: " << (int)casterPosition << "\n";
    //use casterToResolve play WillCompare Animation

    m_CurrentTrack->UpdateTimetrack();

    if (casterPosition >= CasterPosition::CasterA)
    {
        m_State = ResolveState::ResolveSpell;

    }
    else
    {
        std::cout << "\n\tTIED OR NONE\n\n";
        m_State = ResolveState::Waiting;
        m_Timer = 0.5f;
    }

}

void ResolveBattleState::ResolveSpell()
{
    std::cout << "\tResovel Spell: " << m_SpellResolveIndex << "\n";

    CastSpellDetail* spell = m_CurrentTrack->GetSpellList()[m_SpellResolveIndex];

    if (!spell->isCasted)
    {
        switch (spell->OriginalSpell->GetChannelEffectType())
        {
        case ChannelEffectEnum::None:
            spell->doCast = true;
            break;
        case ChannelEffectEnum::Wait:
            if (!spell->doCast)
            {
                CastSpellDetail* newSpell = new CastSpellDetail(*spell);
                newSpell->SelectedTime += newSpell->OriginalSpell->GetChannelTime();
                newSpell->doCast = true;
                m_ResolveBattleManager->Data.Timeline.AddSpellToTimeline(newSpell, true);
                break;
            }
        case ChannelEffectEnum::Active:
            if (!spell->doCast)
            {
                for (int i = spell->SelectedTime + 1; i <= spell->SelectedTime + spell->OriginalSpell->GetChannelTime(); i++)
                {
                    CastSpellDetail* newSpell = new CastSpellDetail(*spell);
                    newSpell->SelectedTime = i;
                    newSpell->doCast = true;
                    m_ResolveBattleManager->Data.Timeline.AddSpellToTimeline(newSpell, true);
                }
            }
            break;
        }

        CasterPosition casterPosition = m_CurrentTrack->GetWillCompareResult();
        CasterPosition targetPosition = casterPosition == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;

        spell->isCasted = true;

        if (spell->doCast)
        {
            CasterController* caster = m_ResolveBattleManager->Data.GetCaster(casterPosition);
            CasterController* target = m_ResolveBattleManager->Data.GetCaster(targetPosition);

            //Damage Calculation
            int damage = spell->GetDamage();
            target->GetEffectManager()->ResolveEffect(EffectResolveType::OnDamageCalculation, 1, &damage);
            target->TakeDamage(damage);

            auto effectType = spell->OriginalSpell->GetSpellEffectType();
            auto effectValue = spell->GetEffectValue();

            if (SpellEffectType::IsEffectTargetEnemy(effectType))
            {
                target->GetEffectManager()->AppliedEffect(effectType, effectValue);
            }
            else
            {
                caster->GetEffectManager()->AppliedEffect(effectType, effectValue);
            }
            //TODO: resolve the spell effect

            m_Timer = 3.0f;
        }
        else
        {
            m_Timer = 0.0f;
        }
    }
    else
    {
        m_Timer = 1.0f;
    }

    m_ResolveBattleManager->Data.Timeline.UpdateTimeline();
    m_State = ResolveState::Waiting;
 
}

void ResolveBattleState::OnBattleStateIn()
{
    m_ResolveBattleManager = BattleManager::GetInstance();
    m_State = ResolveState::ResolveTrack;
    m_TrackResolveIndex = 0;
    m_SpellResolveIndex = 0;
    m_Timer = 0.0f;
}

void ResolveBattleState::OnBattleStateUpdate(float dt)
{
    switch (m_State)
    {
    case ResolveBattleState::ResolveState::ResolveTrack:
        ResolveTrack();
        break;
    case ResolveBattleState::ResolveState::ResolveSpell:
        ResolveSpell();
        break;
    case ResolveBattleState::ResolveState::Waiting:
        m_Timer -= dt;
        if (m_Timer <= 0)
        {
            m_Timer = 0;
            if (m_SpellResolveIndex + 1 < m_CurrentTrack->GetSpellList().size())
            {
                m_SpellResolveIndex++;
                m_State = ResolveState::ResolveSpell;
            }
            else
            {
                m_SpellResolveIndex = 0;
                m_TrackResolveIndex++;
                m_State = ResolveState::ResolveTrack;
            }
        }
        break;
    default:
        break;
    }

    //if(battle end)
    //{}
    //else

    if (m_TrackResolveIndex == 10)
    {
        m_ResolveBattleManager->SetBattleState(BattleState::CastState);
    }
    //m_ResolveBattleManager->SwapCaster();
}

void ResolveBattleState::OnBattleStateOut()
{
    m_ResolveBattleManager->Data.Timeline.CompleteTimeline();
}
