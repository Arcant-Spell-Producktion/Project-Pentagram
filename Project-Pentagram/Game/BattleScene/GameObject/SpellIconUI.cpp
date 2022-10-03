#include "SpellIconUI.h"
#include "Engine/GameStateController.h"

const std::string iconPath = "Sprites/UI/Game/ui_game_spell-icons.png";

SpellIconUI::SpellIconUI(std::string objName):m_Scene(GameStateController::GetInstance()->currentScene)
{
    m_IconObject = m_Scene->CreateGameObject(objName, 4, {9,9,9,9});
    m_IconObject->SetIsAnimationObject(false);
    m_IconObject->SetTexture(iconPath);
    m_IconObject->SetSpriteByIndex(0,0);
    m_IconObject->scale = { 100.0f,100.0f ,1.0f };
}

void SpellIconUI::SetIcon(Element::Type element, int spellIndex)
{
    m_IconObject->SetSpriteByIndex(0, spellIndex);
}

void SpellIconUI::SetPosition(glm::vec3 position)
{
    m_IconObject->position = position;
}
