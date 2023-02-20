#include "CasterEffectBarUI.h"

CasterEffectBarUI::CasterEffectBarUI(int position) :UIObject("EffectBar_" + std::to_string(position))
{
    this->color.a = 0.0f;

    m_Direction = position == 0 ? -1 : 1;

    for (size_t i = 0; i <= (int)SpellEffectEnum::Freeze; i++)
    {
        SpellEffectEnum effEnum = (SpellEffectEnum)i;
        CasterEffectIconUI* newEffIcon = new CasterEffectIconUI(effEnum,0);
        m_EffectIcons.emplace(effEnum, newEffIcon);
        this->SetChildRenderFront(newEffIcon);
    }
}

void CasterEffectBarUI::UpdateEffectIcons(std::vector<EffectDetail_T> effects)
{
    int i = 0;
    for (auto eff: effects)
    {
        CasterEffectIconUI* icon = m_EffectIcons[eff.EffectType];

        icon->ChangeStack(eff.Stack);

        if (icon->IsActive())
        {
            icon->position.x = m_Direction * (-39.0f * i);
            i++;
        }
    }
}
