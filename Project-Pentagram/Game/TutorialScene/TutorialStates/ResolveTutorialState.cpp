#include "ResolveTutorialState.h"
#include "Game/BattleScene/BattleManager.h"

BattleManager* m_ResolveTurManager = nullptr;

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

    m_CurrentTrack = m_ResolveTurManager->Data.Timeline.GetTimetrack(m_TrackResolveIndex);
    m_ResolveTurManager->Data.Timeline.UI->SetTrackerPositionByIndex(m_TrackResolveIndex);
    std::cout << "\tGet Track: " << m_TrackResolveIndex << "\n";

    m_CurrentTrack->UpdateTimetrack();
    m_ResolveTrack = m_CurrentTrack->GetSpellResolveList();
    std::cout << "\tTrack Size: " << m_ResolveTrack.size() << "\n";


    auto position = m_CurrentTrack->GetWillCompareResult();
    if (position >= CasterPosition::TIED)
    {
        if (m_CurrentTrack->DoWillCompare())
        {
            m_ResolveTurManager->Data.WillCompare->StartCompare(position);
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

    m_CurrentSpellDetail = m_ResolveTrack[m_SpellResolveIndex];
    std::cout << "\tResovel Spell: " << m_SpellResolveIndex << " " << m_CurrentSpellDetail->GetSpellDetail()->GetSpellName() << "\n";

    if (!m_CurrentSpellDetail->isCasted)
    {
        int ChannelCount = 0;
        auto spellChannelType = m_CurrentSpellDetail->GetSpellDetail()->GetChannelEffectType();

        m_CurrentSpellDetail->OnCast(&ChannelCount);

        CasterPosition casterPosition = m_CurrentSpellDetail->SpellOwner;

        CasterPosition targetPosition = m_CurrentSpellDetail->GetTarget();

        auto caster = m_ResolveTurManager->Data.GetCaster(casterPosition)->GetCasterObject();

        if (m_CurrentSpellDetail->doCast)
        {
            if (m_CurrentSpellDetail->TriggeredSpell == nullptr && m_CurrentSpellDetail->ParentSpell == nullptr)
            {
                m_CurrentSpellController = m_Dispatcher.SpawnSpell(m_CurrentSpellDetail, targetPosition);
                m_State = ResolveState::PlaySpell;

            }
            else
            {

                /*m_CurrentSpellController = m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell);
                m_State = ResolveState::PlaySpell;*/

                if (!m_CurrentSpellDetail->GetSpellDetail()->GetResolvesEffects().DoCancelSpell())
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

    m_ResolveTurManager->Data.Timeline.UpdateTimeline();

}

void ResolveTutorialState::ResolveDamageCalculation()
{
    std::cout << "\tResovel Damage: " << m_SpellResolveIndex << " " << m_CurrentSpellDetail->GetSpellDetail()->GetSpellName() << "\n";
	m_CurrentSpellDetail->OnResolve();

}

void ResolveTutorialState::OnBattleStateIn()
{
    m_ResolveTurManager = BattleManager::GetInstance();
    m_State = ResolveState::ResolveTrack;
    m_TrackResolveIndex = 0;
    m_SpellResolveIndex = 0;
    m_Timer = 0.0f;

    m_ResolveTurManager->Data.Timeline.UI->SetTrackerActive(true);
    m_ResolveTurManager->Data.Timeline.UI->SetTrackerPositionByIndex(0);

    m_ResolveTurManager->Data.WillCompare->OnCompareDone.AddListener
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
            //m_Dispatcher.DestroySpell(m_CurrentSpellDetail->TriggeredSpell);
            //m_CurrentSpellController = m_Dispatcher.GetControllerBySpell(m_CurrentSpellDetail->ParentSpell);
            m_State = ResolveState::PlaySpell;
        }
        break;
    case ResolveTutorialState::ResolveState::PlaySpell:

        if (m_CurrentSpellController->IsSpellDone())
        {
            ResolveDamageCalculation();

            if (m_CurrentSpellController->Trigger)
            {
                m_Dispatcher.DestroySpell(m_CurrentSpellDetail->ParentSpell);
            }
            else
            {
                m_Dispatcher.DestroySpell(m_CurrentSpellDetail);
            }
            Step();
        }
        else if (m_CurrentSpellController->IsSpellWaitTrigger())
        {
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
        m_ResolveTurManager->SetBattleState(BattleState::StandbyState);
    }
    //m_ResolveTurManager->SwapCaster();
}

void ResolveTutorialState::OnBattleStateOut()
{
    m_ResolveTurManager->Data.Timeline.UI->SetTrackerActive(false);
    m_ResolveTurManager->Data.Timeline.CompleteTimeline();

    m_ResolveTurManager->Data.WillCompare->OnCompareDone.RemoveAllListeners();
}
