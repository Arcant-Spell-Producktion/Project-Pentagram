#pragma once
#include "TutorialNode.h"

class TimeTutorialNode : public TutorialNode
{
private:

public:
    TimeTutorialNode() : TutorialNode(EnemyData(CasterData(CasterStat(10, { 6,6,6,6,6,6 }), Element::Water, CasterPosition::CasterB), CasterType::Minion, CasterMoveSet()))
    {
        m_TutorialPlayerData = new PlayerData(CasterData(CasterStat(10, { 6,6,6,6,6,6 }), Element::Fire, CasterPosition::CasterA));

        m_TutorialText.push_back(
            "As you can see enemy spells\n were added to the banner. This is Timeline."
        );

        m_TutorialText.push_back(
            "Each turn you may cast any amount of the spell\n (If your mana is still available).\nSo this thing will help track the spell in the round."
        );

        m_TutorialText.push_back(
"The spell will be cast from the left most first.\nThe more it appears to the left the faster it will be cast."
        );

        m_TutorialText.push_back("Each spell will have their own cast time\nwhich will determine the speed of that spell."
        );

        m_TutorialText.push_back("However, you may increase or decrease speed of that spell\n by spending mana on the cast time section in the spell circle."
        );

        m_TutorialText.push_back("Now let's try to cast a spell that is faster\n than the enemy spell."
        );
        
    }
};
