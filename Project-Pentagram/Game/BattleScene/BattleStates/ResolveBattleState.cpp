#include "ResolveBattleState.h"
#include <Game/BattleScene/BattleManager.h>


BattleManager* m_ResolveBattleManager = nullptr;

void ResolveBattleState::Step()
{
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

void ResolveBattleState::ResolveTrack()
{
    std::cout << "Resovel Track: " << m_TrackResolveIndex << "\n";

    m_CurrentTrack = m_ResolveBattleManager->Data.Timeline.GetTimetrack(m_TrackResolveIndex);
    m_ResolveBattleManager->Data.Timeline.UI->SetTrackerPositionByIndex(m_TrackResolveIndex);
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

    m_CurrentSpellDetail = m_CurrentTrack->GetSpellList()[m_SpellResolveIndex];

    if (!m_CurrentSpellDetail->isCasted)
    {
        switch (m_CurrentSpellDetail->OriginalSpell->GetChannelEffectType())
        {
        case ChannelEffectEnum::None:
            m_CurrentSpellDetail->doCast = true;
            break;
        case ChannelEffectEnum::Wait:
            if (!m_CurrentSpellDetail->doCast)
            {
                CastSpellDetail* newSpell = new CastSpellDetail(*m_CurrentSpellDetail);
                newSpell->SelectedTime += newSpell->OriginalSpell->GetChannelTime();
                newSpell->doCast = true;
                m_ResolveBattleManager->Data.Timeline.AddSpellToTimeline(newSpell, true);
                break;
            }
        case ChannelEffectEnum::Active:
            if (!m_CurrentSpellDetail->doCast)
            {
                for (int i = m_CurrentSpellDetail->SelectedTime + 1; i <= m_CurrentSpellDetail->SelectedTime + m_CurrentSpellDetail->OriginalSpell->GetChannelTime(); i++)
                {
                    CastSpellDetail* newSpell = new CastSpellDetail(*m_CurrentSpellDetail);
                    newSpell->SelectedTime = i;
                    newSpell->doCast = true;
                    m_ResolveBattleManager->Data.Timeline.AddSpellToTimeline(newSpell, true);
                }
            }
            break;
        }

        CasterPosition casterPosition = m_CurrentTrack->GetWillCompareResult();
        CasterPosition targetPosition = casterPosition == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;

        m_CurrentSpellDetail->isCasted = true;

        if (m_CurrentSpellDetail->doCast)
        {    
            m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail, targetPosition);
            m_State = ResolveState::PlaySpell;

            m_ResolveBattleManager->Data.GetCaster(casterPosition)->GetCasterObject()->PlayAttackAnim(
                [this]()
                {
                    m_CurrentSpellController->Activate();
                });
        }
        else
        {
            m_Timer = 1.0f;
            m_State = ResolveState::Waiting;
        }
    }
    else
    {
        Step();
    }

    m_ResolveBattleManager->Data.Timeline.UpdateTimeline();
 
}

void ResolveBattleState::ResolveDamgeCalculation()
{
    CasterPosition casterPosition = m_CurrentTrack->GetWillCompareResult();
    CasterPosition targetPosition = casterPosition == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;

    CasterController* caster = m_ResolveBattleManager->Data.GetCaster(casterPosition);
    CasterController* target = m_ResolveBattleManager->Data.GetCaster(targetPosition);

    //Damage Calculation
    int damage = m_CurrentSpellDetail->GetDamage();
    target->GetEffectManager()->ResolveEffect(EffectResolveType::OnDamageCalculation, 1, &damage);

    if (!target->TakeDamage(damage)) return;

    auto effectType = m_CurrentSpellDetail->OriginalSpell->GetSpellEffectType();
    auto effectValue = m_CurrentSpellDetail->GetEffectValue();

    if (SpellEffectType::IsEffectTargetEnemy(effectType))
    {
        target->GetEffectManager()->AppliedEffect(effectType, effectValue);
    }
    else
    {
        caster->GetEffectManager()->AppliedEffect(effectType, effectValue);
    }
}

void ResolveBattleState::OnBattleStateIn()
{
    m_ResolveBattleManager = BattleManager::GetInstance();
    m_State = ResolveState::ResolveTrack;
    m_TrackResolveIndex = 0;
    m_SpellResolveIndex = 0;
    m_Timer = 0.0f;

    m_ResolveBattleManager->Data.Timeline.UI->SetTrackerActive(true);
    m_ResolveBattleManager->Data.Timeline.UI->SetTrackerPositionByIndex(0);
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
    case ResolveBattleState::ResolveState::PlaySpell:
        if (m_CurrentSpellController->IsSpellDone())
        {
            m_Dispatcher.DestroySpell(m_CurrentSpellDetail);
            ResolveDamgeCalculation();
            Step();
        }
        break;
    case ResolveBattleState::ResolveState::Waiting:
        m_Timer -= dt;
        if (m_Timer <= 0)
        {
            m_Timer = 0;
            Step();
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
    m_ResolveBattleManager->Data.Timeline.UI->SetTrackerActive(false);
    m_ResolveBattleManager->Data.Timeline.CompleteTimeline();
}
