#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class WillTutorialNode : public TutorialNode
{
private:

public:
    WillTutorialNode() : TutorialNode(
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
        EnemyHP = 30;
        EnemyMana = 10;
        TutorialSpells.push_back({ 1,1,6,1,9 });

        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Fire,
                CasterPosition::CasterA));

        PlayerHP = 10;
        PlayerManaWheel = 6;
        PlayerStartSpell = {1,2,1,1,0};


        m_TutorialEvents.AddStep(
            "Tutorial topic: Will\n\nObjective:\nReduce your opponent's  health to 0"
        );

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });


        m_TutorialEvents.AddStep(
            "Both sides will gain mana at the start of the turn \nby rolling this roulette.\n\nMana gain from roulette will be different \ndepending on each witch you select."
        );

        m_TutorialEvents.AddStep(
            "You can spend mana to customize a spell \nto attack the enemy by adjusting \neach section of the Pentagram.\n\nThe more mana spends more damage/effect \nthe spell can inflict."
        );

        m_TutorialEvents.AddStep(
            "In this tutorial you will learn about WILL.\n\nAdding mana in this section \nwill increase the damage of the spell."
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep("Try defeating this enemy with a single spell by \nadding more WILL into this fireball.\n\n(Press ALT to inspect the spell info.)");

        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep("Now! let's try to defeat the enemy.");

        m_TutorialEvents.AddStep("");

        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "That is the basics of WILL\n\nlet's proceed to the next part of the tutorial.";
        RetryText = "It is too weak, try again with more WILL this time.\n\nPress R to restart";


    }
};
