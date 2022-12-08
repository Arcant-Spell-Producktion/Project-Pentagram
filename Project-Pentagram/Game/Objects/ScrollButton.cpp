#include "ScrollButton.h"

ScrollButton::ScrollButton(std::string text):Button("Scroll-Button_"+text)
{
    this->scale = DefaultScale;
    this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    this->SetTexture("Sprites/UI/Game/ui_game_scroll.png");

    this->SetIsSlicing(false);
    this->SetSlicingBorderSize(160.0f);
    this->SetSlicingBorderMultiplier(0.25f);
    this->SetSlicingType(SlicingType::REPEAT);

    this->onHover = [this](Button* button) { this->scale = ExpandScale; };
    this->unHover = [this](Button* button) { this->scale = DefaultScale; };

    this->textObject.text = text;
    this->textObject.fontSize = 56;
}
