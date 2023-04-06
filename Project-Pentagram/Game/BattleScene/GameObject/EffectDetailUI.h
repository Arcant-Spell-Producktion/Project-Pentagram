#pragma once

#include "Engine/IGameObjectManager.h"
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>
#include "Game/BattleScene/GameObject/CasterEffectIconUI.h"

#include "Utilities/Color.h"

const std::string BurnEffectDetail =
R"(Burning will deal 10
damage x number of stack
at the start of the turn)";
const std::string MarkEffectDetail =
R"(Marking cause 
the next attack damage
receive to x2)";
const std::string FreezeEffectDetail =
R"(Freeze increase
mana used to modify the
cast time by 1)";
const std::string OverflowEffectDetail =
R"(Permanently
increase 1 max mana
during combat)";

class EffectDetailUI : public UIObject
{
    private:
        UIObject* m_Box;
        TextObject* m_TextEffectName;
        TextObject* m_TextEffectDetail;

        CasterEffectIconUI* m_CurrentDetails = nullptr;

        glm::vec3 m_DefaultPosition;

        void SetText(CasterEffectIconUI* details);
        void InitTextObjectComponent(TextObject* textObject, float fontSize);

    public:
        EffectDetailUI(int position, glm::vec3 scale, float fontSize = 28);

        void SetDetail(CasterEffectIconUI* details = nullptr, bool isDefault = false);
};