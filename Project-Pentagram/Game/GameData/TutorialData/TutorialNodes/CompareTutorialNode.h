#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class CompareTutorialNode : public TutorialNode
{
private:

public:
    CompareTutorialNode() : TutorialNode(EnemyData(CasterData(CasterStat(100, { 6,6,6,6,6,6 }), Element::Water, CasterPosition::CasterB), CasterType::Minion, CasterMoveSet()))
    {
        TutorialSpells.push_back({ 1,1,2,1,4 });

        PlayerMana = 4;

        EnemyHP = 100;

        PlayerManaWheel = 1;

        m_TutorialPlayerData = new PlayerData(CasterData(CasterStat(100, { 1,2,3,4,5,6 }), Element::Fire, CasterPosition::CasterA));



        m_TutorialEvents.AddStep("If there is a spell from both sides in the same timeline block.\nIt will be decide by the total WILL stat in that block.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, TutorialEventType::Toggle,false });

        m_TutorialEvents.AddStep(
            "The side that has more WILL stat will get to cast\ntheir spell but with some damage reduction."
        );

        m_TutorialEvents.AddStep(
            "With that you can slow down the speed of that spell\nto make it in the same track with enemy spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Then increase the Will of your spell\nto deny the enemy spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Try to Survive this turn!"
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, TutorialEventType::Toggle,true });
        

        CompleteText = "And now you know how to clash the spell.\nYou may proceed to the next part of the tutorial.";
        RetryText = "Try to clash the enemy spell by adding the spell\nat the same time track but with higher WILL.";


        EnemyMana = 10;
    }
};
#pragma once
