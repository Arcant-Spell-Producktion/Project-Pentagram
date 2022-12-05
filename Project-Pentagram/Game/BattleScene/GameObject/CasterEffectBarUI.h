#pragma once
#include "CasterEffectIconUI.h"
#include <map>

class CasterEffectBarUI : public UIObject
{
private:
    std::map<SpellEffectEnum,CasterEffectIconUI*> m_EffectIcons;

    int m_Direction;
public:
    CasterEffectBarUI(int position);

    void UpdateEffectIcons(std::vector<EffectDetail_T> effects);
};