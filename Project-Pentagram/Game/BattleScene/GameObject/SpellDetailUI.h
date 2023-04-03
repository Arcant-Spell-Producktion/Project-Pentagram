#pragma once
#include "Engine/IGameObjectManager.h"
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

class SpellDetailUI :public UIObject
{
private:
    UIObject* m_Box;
    TextObject* m_TextSpellName;
    TextObject* m_TextSpellDmg;
    TextObject* m_TextSpellEff;
    TextObject* m_TextSpellCha;

    CastSpellDetail* m_CurrentDetails = nullptr;

    glm::vec3 m_DefaultPosition;

    void SetText(CastSpellDetail* details, bool isHideInfo);
    void InitTextObjectComponent(TextObject* textObject, float fontSize);
    void InsertSpellDetailUI(TextObject* textObject, const std::string &newStr);

public:
    SpellDetailUI(int position, float fontSize = 28);
    SpellDetailUI(glm::vec3 position, glm::vec3 scale, float fontSize = 28);

    void SetCasterPosition(CasterPosition position);
    void SetDetail(CastSpellDetail* details = nullptr, bool isDefault = false, bool isHideInfo = false);
};