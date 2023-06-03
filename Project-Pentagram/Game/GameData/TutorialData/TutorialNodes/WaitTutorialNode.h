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
        EnemyHP = 60;
        EnemyMana = 4;
        TutorialSpells.push_back({ 2,1,1,1,7 });

        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Fire,
                CasterPosition::CasterA));

        PlayerHP = 10;
        PlayerManaWheel = 6;

        m_TutorialEvents.AddStep("Tutorial topic: Channeling - Delayed\n\nObjective:\nReduce your opponent's health to 0");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, true });

        m_TutorialEvents.AddStep(
            "In this tutorial we are going to talk about \nchanneling spells.\n\nChanneling is a type of spell that may take \nmore than one turn to Cast or have a lasting effect \nin that turn once Cast."
        );

        m_TutorialEvents.AddStep(
            "There are multiple types of channeling. \n\nThis one is Delayed. \nDelayed type will take time to Conjure up \nthe spell before Casting it."
        );

        m_TutorialEvents.AddStep(
            "The starting track of the Delayed type\nwhen the spell is Cast it will start to Conjure,\nit doesn't count toward total WILL in that\nTime Track in that state, but\nit will count twoards the Time Track that\nthe spell finish Casting."
        );

        m_TutorialEvents.AddStep(
            "To change the type of the spell player can adjust\nthe circle and complexity in the Pentagram, \n\nor use the spell selector on the right."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Each adjustment of this section of the Pentragram\ncost 2 mana per modification.\nSame for the spell selector the further\nyou select away from the first spell  \n\n(Press ALT to toggle spell info)"
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Let's try to Cast a single Delayed spells\nto clash the enemy spell and defeat the enemy.");

        m_TutorialEvents.AddStep("");

        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        RetryText = "Try casting a meteor (Circle 3 complexity 1).\nIt has the same Cast Time as an enemy spell. \n\nPress R to restart";
        CompleteText = "And that is how the channeling spell Delayed works. \n\nLet's proceed to the next part of the tutorial.";


    }
};
