#include "SpellIconUI.h"
#include "Engine/GameStateController.h"
#include <Game/BattleScene/BattleManager.h>

const std::string iconPath = "Sprites/UI/Game/ui_game_spell-icons.png";
const std::string iconVariationPath = "Sprites/UI/Game/ui_game_spell-icon_variation.png";
const std::string iconBorderPath = "Sprites/UI/Game/ui_game_spell-icon_border.png";

SpellIconUI::SpellIconUI(std::string objName, float _scale) :m_ObjectManager(GameStateController::GetInstance()->currentScene), Button(objName)
{
    m_IconSize = _scale;
    m_BorderSize = m_IconSize / 100.0f * 114.0f;

    this->onHover = [this](Button* button)
    {
        UpdateDetail();
    };
    this->unHover = [this](Button* button)
    {
        UpdateDetail();
    };
    this->color.a = 0.0f;
    this->scale = { m_IconSize,m_IconSize ,1.0f };

    m_IconObject = m_ObjectManager->CreateUIObject(objName + "_icon");
    m_IconObject->SetIsAnimationObject(false);
    m_IconObject->SetTexture(iconPath);
    m_IconObject->SetSpriteByIndex(0, 0);
    m_IconObject->scale = { m_IconSize,m_IconSize ,1.0f };

    m_IconOverlay = m_ObjectManager->CreateUIObject(objName + "_icon");
    m_IconOverlay->SetIsAnimationObject(false);
    m_IconOverlay->SetTexture(iconVariationPath);
    m_IconOverlay->SetSpriteByIndex(0, 0);
    m_IconOverlay->scale = { m_IconSize,m_IconSize ,1.0f };

    m_IconBorder = m_ObjectManager->CreateUIObject(objName + "_iconBorder");
    m_IconBorder->SetIsAnimationObject(false);
    m_IconBorder->SetTexture(iconBorderPath);
    m_IconBorder->SetSpriteByIndex(0, 0);
    m_IconBorder->scale = { m_BorderSize , m_BorderSize , 1.0f };

    this->SetChildRenderFront(m_IconObject);
    this->SetChildRenderFront(m_IconOverlay);
    this->SetChildRenderFront(m_IconBorder);

    SetTransparency(false);
}

void SpellIconUI::ToggleIconOverlay(bool flag)
{
    m_toggleOverlay = flag;
    m_IconOverlay->SetActive(m_toggleOverlay);
}

void SpellIconUI::SetTransparency(bool flag)
{
    m_IconObject->color.a = flag ? 0.8f : 1.0f;
    m_IconOverlay->color.a = flag ? 0.6f : 8.0f;
    m_IconBorder->color.a = flag ? 0.8f : 1.0f;

}

void SpellIconUI::SetIcon(CastSpellDetail* spellDetail, bool doCast)
{
    SpellDetail = spellDetail;

    bool isSpelldoCast = doCast;
    switch (SpellDetail->OriginalSpell->GetChannelEffectType())
    {
    case ChannelEffectEnum::None:
        m_BorderIndex = 0;
        m_OverlayIndex = 0;
        break;
    case ChannelEffectEnum::Active:
        m_OverlayIndex = 2;
        m_BorderIndex = isSpelldoCast ? 1 : 0;
        break;
    case ChannelEffectEnum::Wait:
        m_OverlayIndex = 1;
        m_BorderIndex = isSpelldoCast ? 0 : 2;
        break;
    }

    UpdateIcon();
}

void SpellIconUI::SetIsExtra(bool isExtra)
{
    float s = isExtra ? m_IconSize * 1.5f : m_IconSize;

    m_IconOverlay->SetSpriteByIndex(0, isExtra ? 3 : m_OverlayIndex);
    m_IconOverlay->color.a = isExtra ? 1.0f : 0.6f;
    m_IconOverlay->scale = { s,s ,1.0f };

}

void SpellIconUI::SetIsPreview(bool isPreview)
{
    m_isPreview = isPreview;
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
    m_IconOverlay->SetSpriteByIndex(0, m_OverlayIndex);
    m_IconBorder->SetSpriteByIndex(SpellDetail->SpellOwner == CasterPosition::CasterA ? 0 : 1, m_BorderIndex);
    SetTransparency(m_isPreview || SpellDetail->isCasted);
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
