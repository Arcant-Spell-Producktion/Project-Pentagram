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

    m_Click = new UIObject("Click");
    m_Click->position = { 340.0f,-90.0f,0.0f };
    m_Click->scale = { 32.0f,16.0f,0.0f };
    m_Click->SetTexture("Sprites/UI/Game/ui_game_click.png");

    this->SetChildRenderFront(m_Click);

}

void TextBox::OnUpdate(const float& dt)
{
    Button::OnUpdate(dt);
    bool active = textObject.IsRenderComplete();
    m_Click->SetActive(active);
    if (active)
    {
        m_ClickY += dt * 50.0f * direction;

        if(m_ClickY > 20.0f)
        {
            direction = -1;
        }
        else if (m_ClickY < 0.0f)
        {
            direction = 1;
        }

        m_Click->position.y = -90.0f + m_ClickY;
    }
}
