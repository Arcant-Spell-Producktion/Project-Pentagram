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

StageObject::StageObject(Element::Type element) :m_ObjectManager(GameStateController::GetInstance()->currentScene), GameObject("Stage")
{
    this->color.a = 0.0f;

    m_Element = element;

    // TODO:: remove this code
    if(m_Element == Element::Corrupt) m_Element = Element::Earth;

    m_Background = m_ObjectManager->CreateGameObject("Background");
    m_Background->SetTexture(backgroundPath[(int)m_Element]);
    m_Background->scale = { 2160.0f, 1280.0f, 1.0f };

    m_Floor = m_ObjectManager->CreateGameObject("Floor");
    m_Floor->SetTexture(floorPath[(int)m_Element]);
    m_Floor->scale = { 2160.0f, 436.0f, 1.0f };
    m_Floor->position = { 0.0f, -460.0f, 0.0f };
}
