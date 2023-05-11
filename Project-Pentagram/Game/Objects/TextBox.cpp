#include "TextBox.h"

TextBox::TextBox(std::string text) : Button("TextBox")
{
    this->scale = {800.0f,260.0f,1.0f};
    this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    this->SetTexture("Sprites/UI/Game/ui_game_scroll.png");

    this->SetIsSlicing(true);
    this->SetSlicingBorderSize(200.0f);
    this->SetSlicingBorderMultiplier(0.25f);
    this->SetSlicingType(SlicingType::REPEAT);

    textObject.fontSize = 24.0f;
    textObject.isVCenterAlignment = true;
}
