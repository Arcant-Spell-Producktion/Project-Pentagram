#include "ResolveBattleState.h"
#include <Game/BattleScene/BattleManager.h>


BattleManager* m_ResolveBattleManager = nullptr;

void ResolveBattleState::Step()
{
    if (m_SpellResolveIndex + 1 < m_ResolveTrack.size())
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

    m_CurrentTrack->UpdateTimetrack();
	m_ResolveTrack = m_CurrentTrack->GetSpellResolveList();
    std::cout << "\tTrack Size: " << m_ResolveTrack.size() << "\n";


    auto position = m_CurrentTrack->GetWillCompareResult();
    if (position >= CasterPosition::TIED)
    {
        if (m_CurrentTrack->DoWillCompare())
        {
            m_ResolveBattleManager->Data.WillCompare->StartCompare(position);
            m_State = ResolveState::PlayCompare;
        }
        else
        {
            m_State = ResolveState::ResolveSpell;
        }
    }
    else
    {
        std::cout << "\n\tTIED OR NONE\n\n";
        m_State = ResolveState::Waiting;
        m_Timer = 0.5f;
    }


}

void ResolveBattleState::ResolveSpell(int spell_index)
{
    std::cout << "\tResovel Spell: " << m_SpellResolveIndex << "\n";

    m_CurrentSpellDetail = m_ResolveTrack[m_SpellResolveIndex];

    if (!m_CurrentSpellDetail->isCasted)
    {
        int ChannelCount = 0;
        auto spellChannelType = m_CurrentSpellDetail->OriginalSpell->GetChannelEffectType();

        m_CurrentSpellDetail->OnCast(&ChannelCount);

        CasterPosition casterPosition = m_CurrentSpellDetail->SpellOwner;

        CasterPosition targetPosition = casterPosition == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;

        auto caster = m_ResolveBattleManager->Data.GetCaster(casterPosition)->GetCasterObject();
        m_CurrentSpellDetail->isCasted = true;

        if (m_CurrentSpellDetail->doCast)
        {    
            m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail, targetPosition);

            m_State = ResolveState::PlaySpell;

            caster->PlayAttackAnim(
                spellChannelType != ChannelEffectEnum::None,
                [this]()
                {
                    while (m_CurrentSpellController == nullptr) { std::cout << "Debug\n"; };
                    m_CurrentSpellController->Activate();
                });
        }
        else
        {
            caster->PlayChannelAnim(ChannelCount);
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

void ResolveBattleState::ResolveDamageCalculation()
{

    SpellResolveEffect resolveEffect = m_CurrentSpellDetail->OriginalSpell->GetResolvesEffects();
    CasterPosition casterPosition = m_CurrentSpellDetail->SpellOwner;
    CasterPosition targetPosition = m_CurrentSpellDetail->GetTarget();

    CasterController* caster = m_ResolveBattleManager->Data.GetCaster(casterPosition);
    CasterController* target = m_ResolveBattleManager->Data.GetCaster(targetPosition);

    if (resolveEffect.DoCancelDamage())
    {
        caster->SetImmune(m_CurrentSpellDetail->Channel != CastSpellDetail::End);
    }

    if (resolveEffect.DoDamage())
    {
        //Damage Calculation
        int damage = m_CurrentSpellDetail->GetDamage();
        target->GetEffectManager()->ResolveEffect(EffectResolveType::OnDamageCalculation, 1, &damage);
        if (!target->TakeDamage(damage)) return;
    }
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

    m_ResolveBattleManager->Data.WillCompare->OnCompareDone.AddListener
    (
        [this](CasterPosition pos)
        {
            if (pos == CasterPosition::TIED)
            {
				Step();
			}
			else
			{
				m_State = ResolveState::ResolveSpell;
			}
        }
    );
    
}

void ResolveBattleState::OnBattleStateUpdate(float dt)
{
    switch (m_State)
    {
    case ResolveBattleState::ResolveState::ResolveTrack:
        ResolveTrack();
        break;
    case ResolveBattleState::ResolveState::PlayCompare:
        break;
    case ResolveBattleState::ResolveState::ResolveSpell:
        ResolveSpell();
        break;
    case ResolveBattleState::ResolveState::PlaySpell:
        if (m_CurrentSpellController->IsSpellDone())
        {
            m_Dispatcher.DestroySpell(m_CurrentSpellDetail);
            ResolveDamageCalculation();
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
        m_ResolveBattleManager->SetBattleState(BattleState::StandbyState);
    }
    //m_ResolveBattleManager->SwapCaster();
}

void ResolveBattleState::OnBattleStateOut()
{
    m_ResolveBattleManager->Data.Timeline.UI->SetTrackerActive(false);
    m_ResolveBattleManager->Data.Timeline.CompleteTimeline();

    m_ResolveBattleManager->Data.WillCompare->OnCompareDone.RemoveAllListeners();
}
