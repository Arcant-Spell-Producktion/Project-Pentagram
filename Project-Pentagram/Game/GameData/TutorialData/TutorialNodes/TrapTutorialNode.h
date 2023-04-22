#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class TrapTutorialNode : public TutorialNode
{
private:

public:
    TrapTutorialNode() : TutorialNode(
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
        TutorialSpells.push_back({ 1,1,1,1,5 });
        TutorialSpells.push_back({ 1,1,1,1,5 });
        TutorialSpells.push_back({ 1,1,1,1,5 });
        TutorialSpells.push_back({ 1,1,1,1,5 });


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

        m_TutorialEvents.AddStep("Objective:\nSurvive");

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
            "Trap is 1...."
        );

        m_TutorialEvents.AddStep(
            "Trap is 2...."
        );



        m_TutorialEvents.AddStep("Press ALT to toggle spell info\n");

        m_TutorialEvents.AddStep(
            "Try to cancel all enemy spell with Trap Spell"
        );

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "???";
        RetryText = "Try using ฎarth Prison (Circle 2 Complexity 3) to\ncancel all of the spell in that time track";


    }
};
