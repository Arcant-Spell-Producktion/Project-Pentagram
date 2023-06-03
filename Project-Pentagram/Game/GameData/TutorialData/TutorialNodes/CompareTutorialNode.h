#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class CompareTutorialNode : public TutorialNode
{
private:

public:
    CompareTutorialNode() : TutorialNode(EnemyData(CasterData(CasterStat(100, { 6,6,6,6,6,6 }), Element::Water, CasterPosition::CasterB), CasterType::Minion, CasterMoveSet()))
    {
        m_TutorialGoal = TutorialGoal::Survive;

        TutorialSpells.push_back({ 1,1,2,1,9 });

        PlayerMana = 3;

        EnemyHP = 100;

        PlayerManaWheel = 1;

        m_TutorialPlayerData = new PlayerData(CasterData(CasterStat(100, { 1,2,3,4,5,6 }), Element::Fire, CasterPosition::CasterA));

        m_TutorialEvents.AddStep("Tutorial topic: Spell clash\n\nObjective:\nSurvive an attack from the enemy");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, TutorialEventType::Toggle,false });

        m_TutorialEvents.AddStep("If there is a spell from both sides \nin the same Time Track.\n\nIt will Engaged in a Spell Clash to decide\nwhich spell will Activate by comparing the\nhigher total WILL in that Time Track.");

        m_TutorialEvents.AddStep(
            "The Casted spell after a Spell Clash \nwill suffer some damage reduction."
        );

        m_TutorialEvents.AddStep(
            "You can delay your spell Casting speed \nto meet the enemy spell in the same track \nto clash and Cancel out the enemy spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Then increase the WILL of your spell\nto Cancel the enemy spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Now! let's Cancel out an enemy spell by\ndecreasing the CAST TIME of your spell and\n increasing the WILL of your spell."
        );

        m_TutorialEvents.AddStep("");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, TutorialEventType::Toggle,true });
        

        CompleteText = "That is the basics of Spell Clash,\n let's proceed to the next part of the tutorial.";
        RetryText = "Try to Cancel the enemy spell \nby adding the spell with \nhigher WILL in the same Time Track.\n\nPress R to restart";


        EnemyMana = 10;
    }
};
#pragma once
