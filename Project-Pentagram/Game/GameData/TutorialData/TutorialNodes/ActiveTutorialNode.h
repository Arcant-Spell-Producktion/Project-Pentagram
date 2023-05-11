#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class ActiveTutorialNode : public TutorialNode
{
private:

public:
    ActiveTutorialNode() : TutorialNode(
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
        EnemyHP =100;
        EnemyMana = 20;
        TutorialSpells.push_back({ 1,1,3,1,3 });
        TutorialSpells.push_back({ 1,1,4,1,4 });


        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Earth,
                CasterPosition::CasterA));

        PlayerStartSpell = { 1,2,1,1,0 };
        PlayerHP = 10;
        PlayerMana = 4;
        PlayerManaWheel = 5;

        m_TutorialEvents.AddStep("Tutorial topic: Lasting - Trap\n\nObjective:\nSurvive an attack from the enemy");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Focus, false });


        m_TutorialEvents.AddStep(
            "In this tutorial, we are going to talk about channeling spells.\n\nChanneling is a type of spell that may take more than one turn to cast or have a lasting effect in that turn once cast."
        );

        m_TutorialEvents.AddStep(
            "There are multiple types of channeling. \n\nThis one is Lasting. The lasting type will remain active for a certain time on the timeline."
        );


        m_TutorialEvents.AddStep(
            "Let's try casting Lasting spell to defend against an enemy spell"
        );
       
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "And that is how the channeling spell Lasting works. \n\nLet’s proceed to the next part of the tutorial.";
        RetryText = "Try casting an unbreakable shield (Circle 3 Complexity 2)\nIt ignores all of the damage during activation.\n\nPress R to restart";


    }
};
