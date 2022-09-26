#include "StageObject.h"
#include "Engine/GameStateController.h"

const std::string backgroundPath[] =
{
    "Sprites/Stage/Earth/stage_earth_background.png",
    "Sprites/Stage/Fire/stage_fire_background.png",
    "Sprites/Stage/Water/stage_water_background.png",
    "Sprites/Stage/Wind/stage_wind_background.png"
};

const std::string floorPath[] =
{
    "Sprites/Stage/Earth/stage_earth_floor.png",
    "Sprites/Stage/Fire/stage_fire_floor.png",
    "Sprites/Stage/Water/stage_water_floor.png",
    "Sprites/Stage/Wind/stage_wind_floor.png"
};

StageObject::StageObject(Element::Type element) :m_Scene(GameStateController::GetInstance()->currentScene), GameObject("Stage")
{
    this->color.a = 0.0f;

    m_Element = element;

    m_Background = m_Scene->CreateGameObject("Background");
    m_Background->SetTexture(backgroundPath[(int)m_Element]);
    m_Background->scale = { 1920.0f, 1080.0f, 1.0f };

    m_Floor = m_Scene->CreateGameObject("Floor");
    m_Floor->SetTexture(floorPath[(int)m_Element]);
    m_Floor->scale = { 1920.0f, 320.0f, 1.0f };
    m_Floor->position = { 0.0f, -380.0f,0.0f };
}
