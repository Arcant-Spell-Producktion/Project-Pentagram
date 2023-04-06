#pragma once
#include "Game/Spells/SpellEffectType.h"
#include "Engine/IGameObjectManager.h"

class CasterEffectIconUI : public Button
{
private:
    SpellEffectEnum m_Type;
    int m_Stack;
    bool m_IsBeingHover = false;

    TextObject* m_StackText;
public:
    CasterEffectIconUI(SpellEffectEnum type, int n = 0);
    void ChangeStack(int n);
    bool IsBeingHover() const;
    SpellEffectEnum GetEffectType() const;
};