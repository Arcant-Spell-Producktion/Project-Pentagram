#pragma once
#include "CasterEffectIconUI.h"
#include <map>

class CasterEffectBarUI : public UIObject
{
private:
    std::map<SpellEffectEnum,CasterEffectIconUI*> m_EffectIcons;
    CasterEffectIconUI* m_HoverEffectIcon;

    int m_Direction;
public:
    CasterEffectBarUI(int position);

    void OnUpdate(const float& dt) override;

    void UpdateEffectIcons(std::vector<EffectDetail_T> effects);

    CasterEffectIconUI* GetHoverEffectIcon() const;
};