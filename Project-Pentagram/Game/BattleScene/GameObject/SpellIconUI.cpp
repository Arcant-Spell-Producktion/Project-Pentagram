#include "SpellIconUI.h"
#include "Engine/GameStateController.h"
#include <Game/BattleScene/BattleManager.h>

const std::string iconPath = "Sprites/UI/Game/ui_game_spell-icons.png";

SpellIconUI::SpellIconUI(std::string objName) :m_Scene(GameStateController::GetInstance()->currentScene), Button(objName)
{
    this->onHover = [this](Button* button)
    {
        UpdateDetail();
    };
    this->unHover = [this](Button* button)
    {
        UpdateDetail();
    };
    this->color.a = 0.0f;
    this->scale = { 120.0f,120.0f ,1.0f };

    m_IconObject = m_Scene->CreateGameObject(objName + "_icon", 4, { 9,9,9,9 });
    m_IconObject->SetIsAnimationObject(false);
    m_IconObject->SetTexture(iconPath);
    m_IconObject->SetSpriteByIndex(0, 0);
    m_IconObject->scale = { 100.0f,100.0f ,1.0f };
}

void SpellIconUI::SetIcon(Element::Type element, int spellIndex)
{
    m_CurrentElement = element;
    m_CurrentSpellIndex = spellIndex;
    UpdateIcon();
}

void SpellIconUI::SetPosition(glm::vec3 position)
{
    m_IconObject->position = position;
}

void SpellIconUI::SetDetail(CastSpellDetail* spellDetail)
{
    m_SpellDetail = spellDetail;
    SetIcon(m_SpellDetail->OriginalSpell->m_Element,m_SpellDetail->OriginalSpell->m_Index);
}

void SpellIconUI::UpdateIcon()
{
    m_IconObject->SetSpriteByIndex(m_CurrentElement, m_CurrentSpellIndex);
}

void SpellIconUI::UpdateDetail()
{
    if (m_SpellDetail)
    {
        CasterPosition pos = m_SpellDetail->SpellOwner;
        auto caster = BattleManager::GetInstance()->Data.GetCaster(pos);
        if (caster)
        {
            caster->GetCasterUI()->SetDetail(m_SpellDetail);
        }
        
    }
 /*   if (m_SpellDetail != nullptr)
    {
        std::cout << *m_SpellDetail;
    }*/

}
