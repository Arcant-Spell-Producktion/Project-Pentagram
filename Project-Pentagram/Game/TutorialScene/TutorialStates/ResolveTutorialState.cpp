#include "ResolveTutorialState.h"
#include <Game/TutorialScene/TutorialManager.h>


TutorialManager* m_ResolveTutorialManager = nullptr;

void ResolveTutorialState::Step()
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

void ResolveTutorialState::ResolveTrack()
{
    std::cout << "Resovel Track: " << m_TrackResolveIndex << "\n";

    m_CurrentTrack = m_ResolveTutorialManager->Data.Timeline.GetTimetrack(m_TrackResolveIndex);
    m_ResolveTutorialManager->Data.Timeline.UI->SetTrackerPositionByIndex(m_TrackResolveIndex);
    std::cout << "\tGet Track: " << m_TrackResolveIndex << "\n";

    m_CurrentTrack->UpdateTimetrack();
	m_ResolveTrack = m_CurrentTrack->GetSpellResolveList();
    std::cout << "\tTrack Size: " << m_ResolveTrack.size() << "\n";


    auto position = m_CurrentTrack->GetWillCompareResult();
    if (position >= CasterPosition::TIED)
    {
        if (m_CurrentTrack->DoWillCompare())
        {
            m_ResolveTutorialManager->Data.WillCompare->StartCompare(position);
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

void ResolveTutorialState::ResolveSpell(int spell_index)
{
    std::cout << "\tResovel Spell: " << m_SpellResolveIndex << "\n";

    m_CurrentSpellDetail = m_ResolveTrack[m_SpellResolveIndex];

    if (!m_CurrentSpellDetail->isCasted)
    {
        int ChannelCount = 0;
        auto spellChannelType = m_CurrentSpellDetail->OriginalSpell->GetChannelEffectType();

        m_CurrentSpellDetail->OnCast(&ChannelCount);

        CasterPosition casterPosition = m_CurrentSpellDetail->SpellOwner;

        CasterPosition targetPosition = m_CurrentSpellDetail->GetTarget();

        auto caster = m_ResolveTutorialManager->Data.GetCaster(casterPosition)->GetCasterObject();

        if (m_CurrentSpellDetail->doCast)
        {
            if (m_CurrentSpellDetail->TriggeredSpell == nullptr)
            {
				m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail, targetPosition);
				m_State = ResolveState::PlaySpell;

            }
            else
            {

				m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell)->Trigger = true;

                if (!m_CurrentSpellDetail->OriginalSpell->GetResolvesEffects().DoCancelSpell())
                {
					m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail->TriggeredSpell, m_CurrentSpellDetail->TriggeredSpell->GetTarget());
					m_State = ResolveState::PlayTriggeredSpell;
                }
                else
                {
					m_CurrentSpellController = m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell);
					m_State = ResolveState::PlaySpell;
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

    m_ResolveTutorialManager->Data.Timeline.UpdateTimeline();
 
}

void ResolveTutorialState::ResolveDamageCalculation()
{
	m_CurrentSpellDetail->OnResolve();

}

void ResolveTutorialState::OnBattleStateIn()
{
    m_ResolveTutorialManager = TutorialManager::GetInstance();
    m_State = ResolveState::ResolveTrack;
    m_TrackResolveIndex = 0;
    m_SpellResolveIndex = 0;
    m_Timer = 0.0f;

    m_ResolveTutorialManager->Data.Timeline.UI->SetTrackerActive(true);
    m_ResolveTutorialManager->Data.Timeline.UI->SetTrackerPositionByIndex(0);

    m_ResolveTutorialManager->Data.WillCompare->OnCompareDone.AddListener
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

void ResolveTutorialState::OnBattleStateUpdate(float dt)
{
    switch (m_State)
    {
    case ResolveTutorialState::ResolveState::ResolveTrack:
        ResolveTrack();
        break;
    case ResolveTutorialState::ResolveState::PlayCompare:
        break;
    case ResolveTutorialState::ResolveState::ResolveSpell:
        ResolveSpell();
        break;
	case ResolveTutorialState::ResolveState::PlayTriggeredSpell:
		if (m_CurrentSpellController->IsSpellDone())
		{
			m_Dispatcher.DestroySpell(m_CurrentSpellDetail->TriggeredSpell);
			m_CurrentSpellController = m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell);
			m_State = ResolveState::PlaySpell;
		}
		break;
    case ResolveTutorialState::ResolveState::PlaySpell:
        if (m_CurrentSpellController->IsSpellWaitTrigger() ||m_CurrentSpellController->IsSpellDone())
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
        break;

    case ResolveTutorialState::ResolveState::Waiting:
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
        m_ResolveTutorialManager->SetBattleState(TutorialState::StandbyState);
    }
    //m_ResolveTutorialManager->SwapCaster();
}

void ResolveTutorialState::OnBattleStateOut()
{
    m_ResolveTutorialManager->Data.Timeline.UI->SetTrackerActive(false);
    m_ResolveTutorialManager->Data.Timeline.CompleteTimeline();

    m_ResolveTutorialManager->Data.WillCompare->OnCompareDone.RemoveAllListeners();
}
