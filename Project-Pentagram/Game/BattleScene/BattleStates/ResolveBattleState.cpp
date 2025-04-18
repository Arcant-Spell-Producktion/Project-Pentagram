#include "ResolveBattleState.h"
#include <Game/BattleScene/BattleManager.h>

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
    BattleManager& _battleManager = BattleManager::GetInstance();

    std::cout << "Resovel Track: " << m_TrackResolveIndex << "\n";

    m_CurrentTrack = _battleManager.Data.Timeline.GetTimetrack(m_TrackResolveIndex);
    _battleManager.Data.Timeline.UI->SetTrackerPositionByIndex(m_TrackResolveIndex);
    std::cout << "\tGet Track: " << m_TrackResolveIndex << "\n";
    _battleManager.Data.Timeline.UI->HighlightTrack(m_TrackResolveIndex);
    m_CurrentTrack->UpdateTimetrack();
	m_ResolveTrack = m_CurrentTrack->GetSpellResolveList();
    std::cout << "\tTrack Size: " << m_ResolveTrack.size() << "\n";

    int elementA = static_cast<int>(_battleManager.Data.GetCaster(CasterPosition::CasterA)->GetCasterManager()->Data().Element());
    int elementB = static_cast<int>(_battleManager.Data.GetCaster(CasterPosition::CasterB)->GetCasterManager()->Data().Element());


    auto position = m_CurrentTrack->GetWillCompareResult();
    if (position >= CasterPosition::TIED)
    {
        if (m_CurrentTrack->DoWillCompare())
        {
            _battleManager.Data.WillCompare->StartCompare(position, elementA, elementB);
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
    BattleManager& _battleManager = BattleManager::GetInstance();

    if (m_ResolveTrack.size() == 0)
    {
        Step();
        _battleManager.Data.Timeline.UpdateTimeline();
        return;
    }

    m_CurrentSpellDetail = m_ResolveTrack[m_SpellResolveIndex];
    std::cout << "\tResovel Spell: " << m_SpellResolveIndex << " " << m_CurrentSpellDetail->GetSpellDetail()->GetSpellName() << "\n";

    if (!m_CurrentSpellDetail->isCasted)
    {
        int ChannelCount = 0;
        auto spellChannelType = m_CurrentSpellDetail->GetSpellDetail()->GetChannelEffectType();

        m_CurrentSpellDetail->OnCast(&ChannelCount);

        CasterPosition casterPosition = m_CurrentSpellDetail->SpellOwner;

        CasterPosition targetPosition = m_CurrentSpellDetail->GetTarget();

        auto caster = _battleManager.Data.GetCaster(casterPosition)->GetCasterObject();

        if (m_CurrentSpellDetail->doCast)
        {
            if (m_CurrentSpellDetail->TriggeredSpell == nullptr && m_CurrentSpellDetail->ParentSpell == nullptr)
            {
				m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail, targetPosition);
				m_State = ResolveState::PlaySpell;

            }
            else
            {

                if (!m_CurrentSpellDetail->GetSpellDetail()->GetResolvesEffects().DoCancelSpell() && !m_CurrentSpellDetail->GetSpellDetail()->GetResolvesEffects().DoCancelDamage())
                {
					m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail->TriggeredSpell, m_CurrentSpellDetail->TriggeredSpell->GetTarget());
					m_State = ResolveState::PlayTriggeredSpell;
                }
                else
                {
					m_CurrentSpellController = m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell);
                    if (m_CurrentSpellDetail->TriggeredSpell != nullptr || m_CurrentSpellDetail->GetSpellDetail()->GetChannelEffectType() == ChannelEffectEnum::Active)
                    {
                        m_CurrentSpellController->Trigger = true;
					    m_State = ResolveState::PlaySpell;
                    }
                    else
                    {
                        m_Dispatcher.DestroySpell(m_CurrentSpellDetail->ParentSpell);
                        m_CurrentSpellController = nullptr;
                        Step();
                        return;
                    }
                }

            }


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

    _battleManager.Data.Timeline.UpdateTimeline();

}

void ResolveBattleState::ResolveDamageCalculation()
{
    std::cout << "\tResovel Damage: " << m_SpellResolveIndex << " " << m_CurrentSpellDetail->GetSpellDetail()->GetSpellName() << "\n";
	m_CurrentSpellDetail->OnResolve();

}

void ResolveBattleState::OnBattleStateIn()
{
    BattleManager& _battleManager = BattleManager::GetInstance();

    m_State = ResolveState::ResolveTrack;
    m_TrackResolveIndex = 0;
    m_SpellResolveIndex = 0;
    m_Timer = 0.0f;

    _battleManager.Data.Timeline.UI->SetTrackerActive(true);
    _battleManager.Data.Timeline.UI->SetTrackerPositionByIndex(0);

    _battleManager.Data.WillCompare->OnCompareDone.AddListener
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
    BattleManager& _battleManager = BattleManager::GetInstance();

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
	case ResolveBattleState::ResolveState::PlayTriggeredSpell:
		if (m_CurrentSpellController->IsSpellDone())
		{
			//m_Dispatcher.DestroySpell(m_CurrentSpellDetail->TriggeredSpell);
			//m_CurrentSpellController = m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell);
			m_State = ResolveState::PlaySpell;
		}
		break;
    case ResolveBattleState::ResolveState::PlaySpell:
        
        if(m_CurrentSpellController->IsSpellDone())
        {
            if (m_CurrentSpellController->Trigger)
            {
                m_Dispatcher.DestroySpell(m_CurrentSpellDetail->ParentSpell);
            }
            else
            {
                m_Dispatcher.DestroySpell(m_CurrentSpellDetail);
            }

            ResolveDamageCalculation();
            Step();
        }
        else if (m_CurrentSpellController->IsSpellWaitTrigger())
        {
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
        _battleManager.SetBattleState(BattleState::StandbyState);
    }
    //_battleManager.SwapCaster();
}

void ResolveBattleState::OnBattleStateOut()
{
    BattleManager& _battleManager = BattleManager::GetInstance();

    _battleManager.Data.Timeline.UI->SetTrackerActive(false);
    _battleManager.Data.Timeline.CompleteTimeline();
    _battleManager.Data.EndRound();
    _battleManager.Data.WillCompare->OnCompareDone.RemoveAllListeners();
}
