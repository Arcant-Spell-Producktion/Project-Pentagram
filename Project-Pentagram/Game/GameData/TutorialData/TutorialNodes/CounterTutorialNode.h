#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class CounterTutorialNode : public TutorialNode
{
private:

public:
    CounterTutorialNode() : TutorialNode(
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
        EnemyHP = 100;
        EnemyMana = 20;
        TutorialSpells.push_back({ 1,3,6,1,7 });


        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Earth,
                CasterPosition::CasterA));

        PlayerStartSpell = { 1,1,1,1,0 };
        PlayerHP = 10;
        PlayerMana = 2;
        PlayerManaWheel = 5;

        m_TutorialEvents.AddStep("Tutorial topic: Channeling - Counter\n\nObjective:\nSurvive an attack from the enemy");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, false });


        m_TutorialEvents.AddStep(
            "In this tutorial we are going to talk about \nchanneling spells.\n\nChanneling is a type of spell that may take \nmore than one turn to Cast or have a lasting effect \nin that turn once Cast."
        );

        m_TutorialEvents.AddStep(
            "There are multiple types of channeling.\n\nThis one is Counter.\nCounter type when cast will do nothing \nuntil the Opponent Spell that targeted the another Unit\nActivate during it's Activation."
        );


        m_TutorialEvents.AddStep(
            "Let's try casting a single Counter spell \nto defend against an enemy spell."
        );

        m_TutorialEvents.AddStep("");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "And that how the channeling spell Counter work.\n\nLet's proceed to the next part of the tutorial.";
        RetryText = "Try using Reflect Shield (Circle 3 Complexity 1) \n\nIt can Cancel a spell that targets you \nin the Time Track and reflect the damage \nto the enemy instead.\n\nPress R to restart";


    }
};
