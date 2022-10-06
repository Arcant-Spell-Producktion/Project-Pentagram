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

    m_IconObject = m_Scene->CreateUIObject(objName + "_icon");
    m_IconObject->SetIsAnimationObject(false);
    m_IconObject->SetTexture(iconPath);
    m_IconObject->SetSpriteByIndex(0, 0);
    m_IconObject->scale = { 100.0f,100.0f ,1.0f };
    this->SetChildRenderBack(m_IconObject);
}

void SpellIconUI::SetIcon(CastSpellDetail* spellDetail)
{
    SpellDetail = spellDetail;
    UpdateIcon();
}

void SpellIconUI::SetPosition(glm::vec3 position)
{
    m_IconObject->position = position;
}


void SpellIconUI::UpdateIcon()
{
    m_CurrentElement = SpellDetail->OriginalSpell->m_Element;
    m_CurrentSpellIndex = SpellDetail->OriginalSpell->m_Index;

    m_IconObject->SetSpriteByIndex(m_CurrentElement, m_CurrentSpellIndex);

    if (SpellDetail->isCasted)
    {
        m_IconObject->color.a = 0.8f;
    }
}

void SpellIconUI::UpdateDetail()
{
    if (SpellDetail)
    {
        CasterPosition pos = SpellDetail->SpellOwner;
        auto caster = BattleManager::GetInstance()->Data.GetCaster(pos);
        if (caster)
        {
            caster->GetCasterUI()->SetDetail(SpellDetail);
        }
        
    }
 /*   if (SpellDetail != nullptr)
    {
        std::cout << *SpellDetail;
    }*/

}
