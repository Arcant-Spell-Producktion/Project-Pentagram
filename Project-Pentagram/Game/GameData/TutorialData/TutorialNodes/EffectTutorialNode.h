#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class EffectTutorialNode : public TutorialNode
{
private:

public:
    EffectTutorialNode() : TutorialNode(
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
        EnemyHP = 50;
        EnemyMana = 10;
        TutorialSpells.push_back({ 1,1,6,1,11 });

        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Fire,
                CasterPosition::CasterA));

        PlayerHP = 10;
        PlayerManaWheel = 6;
        PlayerStartSpell = {2,1,1,1,0};

        m_TutorialEvents.AddStep("Objective:\nReduce your opponent health to 0");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });

        m_TutorialEvents.AddStep(
            "You can custom each attribute of the spell\nby spending mana."
        );

        m_TutorialEvents.AddStep(
            "In this tutorial is about EFFECT.\nAdding mana to this attribute make the Spell Effect stronger."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Focus, true });


        m_TutorialEvents.AddStep("Each spell have it own Effect\nThis one is BURNING, which deal damage at the\start of a round, base on the stack it have.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep("Press ALT to toggle spell info\n");
        m_TutorialEvents.AddStep(
            "Try to defeat the enemy with the burning effect.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "That the basic of Effect,\n continue to the next tutorial to learn more.";
        RetryText = "Try to Add more mana to the Effect to\n make burning stack higher.";


    }
};
