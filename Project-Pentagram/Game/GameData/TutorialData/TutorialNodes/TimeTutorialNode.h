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

        m_TutorialEvents.AddStep("As you can see enemy spells\n were added to the banner. This is Timeline.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });

        m_TutorialEvents.AddStep(
            "Each turn you may cast any amount of the spell\n (If your mana is still available).\nSo this thing will help track the spell in the round."
        );

        m_TutorialEvents.AddStep(
            "The spell will be cast from the left most first.\nThe more it appears to the left the faster it will be cast."
        );

        m_TutorialEvents.AddStep(
            "Each spell will have their own cast time\nwhich will determine the speed of that spell."
        );

        m_TutorialEvents.AddStep("However, you may increase or decrease speed of that spell\n by spending mana on the cast time section in the spell circle.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep(
            "Now let's try to cast a spell that is faster\n than the enemy spell.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        CompleteText = "And that is how the timeline work.\nNow you may proceed to the next part of the tutorial.";
        RetryText = "Try to cast the spell before the enemy spell\nBy increasing the speed of the spell.";


    }
};
