#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class EffectTutorialNode : public TutorialNode
{
private:

public:
    EffectTutorialNode() : TutorialNode(
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
        EnemyHP = 40;
        EnemyMana = 10;
        TutorialSpells.push_back({ 1,1,6,1,11 });

        m_TutorialPlayerData = new PlayerData(
            CasterData(
                CasterStat(
                    100,
                    { 1,2,3,4,5,6 }),
                Element::Fire,
                CasterPosition::CasterA));

        PlayerHP = 10;
        PlayerManaWheel = 6;
        PlayerStartSpell = {2,1,1,1,0};

        m_TutorialEvents.AddStep("Tutorial topic: Effect\n\nObjective: \nReduce your opponent's  health to 0");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, false });

        m_TutorialEvents.AddStep(
            "In this game, you can spend mana \nto customize a spell to attack the enemy \nby adjusting each section of the spell circle.\n\nThe more mana spends more damage/effect \nthe spell can inflict."
        );

        m_TutorialEvents.AddStep(
            "In this tutorial, you will learn about Effect.\n\nEach spell have its own effect.\nAdding mana to it will \nempower that effect. "
        );
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Toggle, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB,TutorialEventType::Focus, true });


        m_TutorialEvents.AddStep("There are many effects in the game.\n\nEx: Burning: \nUnit with burning will take 10 damage per stack \nat the start of the turn.\n(Stack decrease by 1 after taking damage)");
        m_TutorialEvents.AddEvent({ MainObjectEnum::Null,TutorialEventType::Focus, true });

        m_TutorialEvents.AddStep("Try to use a single flame pillar \nto kill the enemy by \nthe start of the next round.\n\n(Press ALT to inspect the information of the spell.)");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, TutorialEventType::Toggle,true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton,TutorialEventType::Toggle, true });

        CompleteText = "That is the basics of Effect,\n lets proceed to the next part of the tutorial.";
        RetryText = "This needs some more fire\ntry adding more effect this time.\n\nPress R to restart";


    }
};
