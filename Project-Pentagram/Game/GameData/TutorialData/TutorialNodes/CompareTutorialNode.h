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



        m_TutorialEvents.AddStep("Tutorial topic: Spell clash\n\nObjective:\nReduce your opponent health to 0");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, TutorialEventType::Toggle,false });

        m_TutorialEvents.AddStep("If there is a spell from both sides \nin the same Time Track.\n\nIt will decide which spell will be cast \nby comparing the higher total WILL in that Time track.");

        m_TutorialEvents.AddStep(
            "The casted spell after a spell clash \nwill suffer some damage reduction."
        );

        m_TutorialEvents.AddStep(
            "you can delay you spell casting speed \nto meet the enemy spell in the same track \nto clash and cancel out the enemy spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Then increase the Will of your spell\nto deny the enemy spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Now lets cancel out an enemy spell by\ndecreasing the cast time of your spell and\n increasing the WILL of your spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, TutorialEventType::Toggle,true });
        

        CompleteText = "That is the basics of spell clash,\n lets proceed to the next part of the tutorial.";
        RetryText = "Try to cancel the enemy spell \nby adding the spell with \nhigher WILL in the same Time track.\n\nPress R to restart";


        EnemyMana = 10;
    }
};
#pragma once
