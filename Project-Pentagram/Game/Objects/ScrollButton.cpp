#include "ScrollButton.h"

ScrollButton::ScrollButton(std::string text):Button("Scroll-Button_"+text)
{
    this->scale = DefaultScale;
    this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    this->SetTexture("Sprites/UI/Game/ui_game_scroll.png");

    this->SetIsSlicing(true);
    this->SetSlicingBorderSize(200.0f);
    this->SetSlicingBorderMultiplier(0.25f);
    this->SetSlicingType(SlicingType::REPEAT);

    this->unHover = [this](Button* button) { 
        if (!m_isExpand)
        {
            this->scale = DefaultScale;
        }
    };

    this->onHover = [this](Button* button) {
            this->scale = ExpandScale;
    };

    this->onClick = [this](Button* button) {
        if (m_isToggle)
        {
            m_isExpand = !m_isExpand;
            this->scale = m_isExpand ? ExpandScale : DefaultScale;
        }
    };

    this->textObject.text = text;
    this->textObject.fontSize = 56;
    this->textObject.color = { 1.0f,1.0f,1.0f,1.0f };
    this->textObject.outlineColor = { 0.0f,0.0f,0.0f,1.0f };
}

void ScrollButton::SetToggleButton(bool isToggle)
{
    m_isToggle = isToggle;
}

void ScrollButton::SetExpand(bool isExpand)
{
    m_isExpand = isExpand;
    this->scale = m_isExpand ? ExpandScale : DefaultScale;
}
