#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class WaitTutorialNode : public TutorialNode
{
private:

public:
    WaitTutorialNode() : TutorialNode(
        EnemyData(
            CasterData(
                CasterStat(
                    100,
                    { 6,6,6,6,6,6 }),
                Element::Water,
                CasterPosition::CasterB),
            CasterType::Minion,
            CasterMoveSet()))
    {
        EnemyHP = 65;
        EnemyMana = 4;
        TutorialSpells.push_back({ 2,1,1,1,6 });

        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Fire,
                CasterPosition::CasterA));

        PlayerHP = 10;
        PlayerManaWheel = 6;

        m_TutorialEvents.AddStep("Objective:\nReduce your opponent health to 0");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, true });

        m_TutorialEvents.AddStep(
            "In this tutorial we are going to talk about\nchanneling spells. Channeling spell is a spell that\ntake more than one turn to cast or effect active\nmore than one turn."
        );

        m_TutorialEvents.AddStep(
            "Wait spell is bruh"
        );

        m_TutorialEvents.AddStep(
            "This is CIRCLE. It control type of the spell\nthat you are using, this use 2 mana to change"
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "This is COMPLEX\n along with CIRCLE it control type\nof the spell, using these 2 combine to\ncreate unique spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Focus, true });


        m_TutorialEvents.AddStep("Press ALT to toggle spell info\n");
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Try to cast a channeling wait spell and defeat the enemy.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        RetryText = "Using meteor(Circle 3 complexity 1) will have\nthe same time as enemy spell.";
        CompleteText = "And that how the channeling spell Wait work.\nYou may proceed to the next part of the tutorial.";


    }
};
