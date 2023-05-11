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

        m_TutorialEvents.AddStep("Tutorial topic: Channeling - Delayed\n\nObjective:\nReduce your opponent health to 0");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, true });

        m_TutorialEvents.AddStep(
            "In this tutorial we are going to talk about \nchanneling spells.\n\nChanneling is a type of spell \nthat may take more than one turn \nto cast or have a lasting effect \nin that turn once cast."
        );

        m_TutorialEvents.AddStep(
            "There are multiple types of channeling. \n\nThis one is Delayed. \nWait type will take time to charge up \nthe spell before casting it."
        );

        m_TutorialEvents.AddStep(
            "The starting track of the Delayed type, \nwhen the spell is launched, \nwill not count toward total WILL in that Time track, \nbut will count in the Time track that the spell landed."
        );

        m_TutorialEvents.AddStep(
            "To change the type of the spell \nplayer can adjust the circle and complexity \nin the spell circle."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Each adjustment of this section \ncost 2 mana per modification."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Focus, true });


        m_TutorialEvents.AddStep("Press ALT to toggle spell info\n");
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Lets try to cast some channeling spells\nclash the enemy spell and defeat them.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        RetryText = "Try casting a meteor(Circle 3 complexity 1).\nIt has the same cast time as an enemy spell. \n\nPress R to restart";
        CompleteText = "And that is how the channeling spell Delayed works. \n\nLets proceed to the next part of the tutorial.";


    }
};
