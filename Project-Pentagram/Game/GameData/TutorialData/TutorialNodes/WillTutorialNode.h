#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class WillTutorialNode : public TutorialNode
{
private:

public:
    WillTutorialNode() : TutorialNode(
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
        EnemyHP = 20;
        EnemyMana = 10;
        TutorialSpells.push_back({ 1,1,6,1,5 });

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

        m_TutorialEvents.AddStep(
            "You can custom each attribute of the spell\nby spending mana."
        );

        m_TutorialEvents.AddStep(
            "You gain mana at start of your turn from the roulette.\n The stronger you get the more mana you gain."
        );

        m_TutorialEvents.AddStep(
            "In this tutorial is about WILL.\nAdding mana to this attribute make the spell stronger."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep("Press ALT to toggle spell info\n");
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Try to defeat the enemy.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "That the basic of WILL,\n continue to the next tutorial to learn more.";
        RetryText = "Try to Add more mana to the WILL to\n make fire ball damage higher.";


    }
};
