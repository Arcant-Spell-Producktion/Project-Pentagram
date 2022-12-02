#include "PentagramCircleUI.h"

PentagramCircleUI::PentagramCircleUI(IGameObjectManager* scene): UIObject("PentagramCircleUI")
{
    this->color.a = 0.0f;

    for (size_t i = 0; i < 4; i++)
    {
        float radius = 460.0f;

        UIObject* circle = scene->CreateUIObject("Circle_" + std::to_string(i));

        circle->SetIsAnimationObject(false);
        circle->scale = { radius,radius,1.0f };
        circle->SetSpriteByIndex(i, 0);
        circle->SetTexture("Sprites/UI/Game/ui_game_pentagram.png");
        circle->SetActive(!(i > 1));
        if (i > 0)
        {
            circle->color.a = 0.8f;
        }

        m_PentragramObj.push_back(circle);
        this->SetChildRenderBack(circle);
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

void PentagramCircleUI::SetCircle(int value)
{
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
    if (scale < 450.0f || scale > 480.0f)
    {
        expand *= -1;
    }

    for (size_t i = 1; i < 4; i++)
    {
        int direction = i % 2 == 0 ? 1 : -1;
        m_PentragramObj[i]->rotation += (dt * speed * i * direction);


        m_PentragramObj[i]->scale = { scale,scale,1.0f };
    }
}
