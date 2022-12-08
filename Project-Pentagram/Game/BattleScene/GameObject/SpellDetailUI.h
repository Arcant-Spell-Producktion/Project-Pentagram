#pragma once
#include "Engine/IGameObjectManager.h"
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

class SpellDetailUI :public UIObject
{
private:
    UIObject* m_Box;
    TextObject* m_Texts;

    CastSpellDetail* m_CurrentDetails = nullptr;

    glm::vec3 m_DefaultPosition;

    void SetText(CastSpellDetail* details);

public:
    SpellDetailUI(int position);

    void SetDetail(CastSpellDetail* details = nullptr, bool isDefault = false);
};