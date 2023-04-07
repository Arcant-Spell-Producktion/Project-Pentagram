#pragma once
#include "TutorialEvent.h"
#include "TutorialNode.h"

class TimeTutorialNode : public TutorialNode
{
private:

public:
    TimeTutorialNode() : TutorialNode(EnemyData(CasterData(CasterStat(100, { 6,6,6,6,6,6 }), Element::Water, CasterPosition::CasterB), CasterType::Minion, CasterMoveSet()))
    {
        std::array<PentagramData_T, 20> moveSet;
        moveSet.fill({ 1,1,6,1,0 });
        CasterMoveSet enemyMove(moveSet);
        m_Enemy.SetMove(enemyMove);

        m_TutorialPlayerData = new PlayerData(CasterData(CasterStat(100, { 6,6,6,6,6,6 }), Element::Fire, CasterPosition::CasterA));

        m_TutorialEvents.AddStep("As you can see enemy spells\n were added to the banner. This is Timeline.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramCircleB, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramComplexB, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramWillB, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramEffectB, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, false });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, false });

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

        m_TutorialEvents.AddStep(
            "Now let's try to cast a spell that is faster\n than the enemy spell.");
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramTimeB, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PentagramScroll, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::CastButton, true });
        m_TutorialEvents.AddEvent({ MainObjectEnum::PassButton, true });

        EnemyMana = 10;
    }
};
