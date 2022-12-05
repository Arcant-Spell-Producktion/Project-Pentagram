#pragma once
#include "Game/Spells/SpellEffectType.h"
#include "Engine/IGameObjectManager.h"

class CasterEffectIconUI : public UIObject
{
private:
    SpellEffectEnum m_Type;
    int m_Stack;

    TextObject* m_StackText;
public:
    CasterEffectIconUI(SpellEffectEnum type, int n = 0);
    void ChangeStack(int n);
};