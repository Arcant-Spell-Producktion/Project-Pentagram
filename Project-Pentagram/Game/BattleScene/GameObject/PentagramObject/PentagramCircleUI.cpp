#include "PentagramCircleUI.h"

const std::string pentagramCircleTexture[] =
{
    "Sprites/UI/Game/ui_game_pentagram_Earth.png",
    "Sprites/UI/Game/ui_game_pentagram_Fire.png",
    "Sprites/UI/Game/ui_game_pentagram_Water.png",
    "Sprites/UI/Game/ui_game_pentagram_Wind.png",
};

PentagramCircleUI::PentagramCircleUI(IGameObjectManager* scene): UIObject("PentagramCircleUI")
{
    this->position = { 0.0f, PENTAGRAM_CIRCLE_OFFSET_Y, 0.0f };
    this->color.a = 0.0f;

    for (size_t i = 0; i < 4; i++)
    {
        float radius = 400.0f;

        UIObject* circle = new UIObject("Circle_" + std::to_string(i));

        circle->SetIsAnimationObject(false);
        circle->scale = { radius, radius, 1.0f };
        circle->SetSpriteByIndex(i, 0);
        circle->SetTexture(pentagramCircleTexture[0]);
        circle->SetActive(!(i > 1));
        if (i > 0)
        {
            circle->color.a = 0.8f;
        }

        m_PentragramObj.push_back(circle);
        this->SetChildRenderBack(circle);
    }
}

void PentagramCircleUI::SetElement(int value)
{
    for (auto circle : m_PentragramObj)
    {
        circle->SetTexture(pentagramCircleTexture[value]);
    }
}

void PentagramCircleUI::SetPentagramUI(int circle, int complex)
{
    SetCircle(circle);
    SetComplex(complex);
}

void PentagramCircleUI::UpdateCircleUI(PentagramEvent e)
{
    switch (e.Field)
    {
    case PentagramField::Circle:
        SetCircle(e.Value);
        break;
    case PentagramField::Complex:
        SetComplex(e.Value);
        break;
    }
}

int PentagramCircleUI::GetComplexValue()
{
    return m_ComplexValue;
}
int PentagramCircleUI::GetCircleValue()
{
    return m_CircleValue;
}

void PentagramCircleUI::SetCircle(int value)
{
    m_CircleValue = value;
    for (size_t i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            m_PentragramObj[i]->SetSpriteByIndex(i, value - 1);
        }
        m_PentragramObj[i]->SetActive(i <= value);
    }
}

void PentagramCircleUI::SetComplex(int value)
{
    m_ComplexValue = value;
    for (size_t i = 1; i < 4; i++)
    {
        m_PentragramObj[i]->SetSpriteByIndex(i, value - 1);
    }
}

int expand = 1;
void PentagramCircleUI::OnUpdate(const float& dt)
{
    float speed = 10.0f;
    float scale = m_PentragramObj[1]->scale.x + dt * 20.0f * expand;
    if (scale < 380.0f || scale > 420.0f)
    {
        expand *= -1;
    }

    for (size_t i = 1; i < 4; i++)
    {
        int direction = i % 2 == 0 ? 1 : -1;
        m_PentragramObj[i]->rotation += (dt * speed * i * direction);


        m_PentragramObj[i]->scale = { scale, scale, 1.0f };
    }
}
