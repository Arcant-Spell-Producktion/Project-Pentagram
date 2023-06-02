#include "StageObject.h"
#include "Engine/GameStateController.h"

const std::string backgroundPath[] =
{
    "Sprites/Stage/Earth/stage_earth_background.png",
    "Sprites/Stage/Fire/stage_fire_background.png",
    "Sprites/Stage/Water/stage_water_background.png",
    "Sprites/Stage/Wind/stage_wind_background.png",
    "Sprites/Stage/Corrupt/stage_corrupt_background.png"
};

const std::string floorPath[] =
{
    "Sprites/Stage/Earth/stage_earth_floor.png",
    "Sprites/Stage/Fire/stage_fire_floor.png",
    "Sprites/Stage/Water/stage_water_floor.png",
    "Sprites/Stage/Wind/stage_wind_floor.png",
    "Sprites/Stage/Corrupt/stage_corrupt_floor.png"
};

StageObject::StageObject(Element::Type element) : GameObject("Stage")
{
    this->color.a = 0.0f;

    m_Background = new GameObject("Background");
    m_Background->scale = { 2160.0f, 1280.0f, 1.0f };

    m_Floor = new GameObject("Floor");

    m_FadeScreen = new GameObject("FadeScreen");
    m_FadeScreen->scale = { 2160.0f, 1280.0f, 1.0f };
    m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };

    this->SetChildRenderBack(m_Background);
    this->SetChildRenderBack(m_Floor);
    this->SetChildRenderFront(m_FadeScreen);

    SetElement(element);
}

void StageObject::SetElement(Element::Type element)
{
    m_Element = element;

    m_Background->SetTexture(backgroundPath[(int)m_Element]);

    glm::vec3 floor_scale = { 2160.0f, 436.0f, 1.0f };
    glm::vec3 floor_position = { 0.0f, -460.0f, 0.0f };

    m_Floor->SetTexture(floorPath[(int)m_Element]);
    if (m_Element == Element::Corrupt)
    {
        floor_scale.y = 564.0f;
        floor_position.y = -396.5f;
    }

    m_Floor->scale = floor_scale;
    m_Floor->position = floor_position;
}

void StageObject::FadeToBlack()
{
    m_FadeIn = true;
    m_FadeTimer = 0.0f;
}

void StageObject::OnUpdate(const float& dt)
{
    GameObject::OnUpdate(dt);

    if (m_FadeIn)
    {
        m_FadeTimer += dt;
        m_FadeScreen->color.a = m_FadeTimer / m_FadeSpeed;
        if (m_FadeTimer > m_FadeSpeed) m_FadeIn = false;
    }
}
