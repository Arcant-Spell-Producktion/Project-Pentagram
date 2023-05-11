#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class TimeTutorialNode : public TutorialNode
{
private:

public:
    TimeTutorialNode() : TutorialNode(
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
        TutorialSpells.push_back({ 1,1,6,1,0 });

        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100, 
                    { 1,2,3,4,5,6 }),
                Element::Fire, 
                CasterPosition::CasterA));

        EnemyMana = 10;
        PlayerManaWheel = 1;

        m_TutorialEvents.AddStep("Tutorial topic: Timeline\n\nObjective:\nReduce your opponent's health to 0.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });

        //add focus on timeline here
        m_TutorialEvents.AddStep(
            "The enemy spells is added to the TIMELINE.\n\nEach column in the timeline is TIME TRACK."
        );
        //m_TutorialEvents.AddEvent({ MainObjectEnum::Timeline,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "You can cast as many spells as you want \neach turn if you have enough mana for it.\n\nThe timeline will help you \nkeep track of the spell cast that round."
        );

        m_TutorialEvents.AddStep(
            "The spell will start casting \nfrom the left-most TIME TRACK  to the right."
        );

        m_TutorialEvents.AddStep(
            "Each spell has its own cast time \nand will determine the spot on the timeline."
        );

        m_TutorialEvents.AddStep("You can add mana to the spell to hasten it\n\n(delaying the spell don't take mana)");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Now! let's try casting a single spell \nthat's faster that the enemy spell.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        CompleteText = "And thats the basic of how timeline work.\n\nLet's proceed to the next part of the tutorial.";
        RetryText = "You need to be faster \ntry adjusting the spell to the left.\n\nPress R to restart";


    }
};
