﻿#include "Engine/GameStateController.h"
#include "TimetrackUI.h"

#include "Game/BattleScene/BattleManager.h"

const int maxIcon = 7;

const float trackY = -70.0f;

const float trackWidth = 120.0f;

const float scaleDefault = 200.0f;
const float iconSize = 80.0f;
const float iconGap = 17.5f;

std::string TimelineTrackSprite[2] =
{
    "Sprites/UI/Game/Timeline/ui_game_timeline_banner-borderless.png",
    "Sprites/UI/Game/Timeline/ui_game_timeline_banner-border.png"
};

TimetrackUI::TimetrackUI(int index, SpellTimetrack* track, std::function<void(bool doExpand)> expand):m_TrackPtr(track),m_ObjectManager(GameStateController::GetInstance().currentScene), UIObject("TrackUI_" + std::to_string(index))
{
    m_TrackIndex = index;

    this->position.x = m_TrackIndex * trackWidth - (trackWidth * 5);
    this->position.y = trackY;
    this->color.a = 0.0f;

    m_Box = new UIObject("TrackUI_Box_" + std::to_string(m_TrackIndex));
    m_Box->scale = { trackWidth, scaleDefault, 1.0f };

    m_IconParent = new UIObject("TrackUI_IconParent_" + std::to_string(m_TrackIndex));
    m_IconParent->color.a = 0.0f;
    m_IconParent->position.y += 57.0f;

    m_Box->SetTexture(TimelineTrackSprite[0]);
    m_Box->SetIsSlicing(true);
    m_Box->SetSlicingBorderSize(32.0f);
    m_Box->SetSlicingBorderMultiplier(1.0f);
    m_Box->SetSlicingType(SlicingType::STRETCH);


    m_PreviewIcon = new SpellIconUI("PreviewIcon_" + std::to_string(m_TrackIndex), iconSize);
    m_PreviewIcon->SetActive(false);

    m_ExpandButton = new Button("Expand_" + std::to_string(m_TrackIndex));
    m_ExpandButton->SetIsSlicing(false);
    m_ExpandButton->SetTexture("Sprites/UI/Game/Timeline/ui_game_timeline_button.png");
    m_ExpandButton->SetIsAnimationObject(false);
    m_ExpandButton->scale = { trackWidth , trackWidth/4.0f , 1.0f };
    m_ExpandButton->SetSpriteByIndex(0,0);

    m_ExpandButton->onHover = [this](Button* button)
    {
        int index = !m_IsExpanded ? 0 : 1;
        m_ExpandButton->SetSpriteByIndex(index, 1);
    };

    m_ExpandButton->unHover = [this](Button* button)
    {
        int index = !m_IsExpanded ? 0 : 1;
        m_ExpandButton->SetSpriteByIndex(index, 0);
    };

    m_ExpandButton->onClick = [this, expand](Button* button)
    {
        std::cout << "TRY EXPAND" << m_TrackIndex << "\n";
        m_IsExpanded = !m_IsExpanded;

        expand(m_IsExpanded);

        auto index = m_ExpandButton->GetCurrentAnimationIndex();
        m_ExpandButton->SetSpriteByIndex((index.x + 1)%2, 0);
    };

    m_WillCompareUI = new WillCompareUI(m_TrackIndex);
    m_WillCompareUI->position = { 0.0f, scaleDefault / 2.0f - 10.0f , 0.0f };

    this->SetChildRenderBack(m_Box);
    this->SetChildRenderFront(m_IconParent);
    this->SetChildRenderFront(m_WillCompareUI);
    m_IconParent->SetChildRenderFront(m_PreviewIcon);
    m_Box->SetChildRenderFront(m_ExpandButton);

    SetExpandButtonScale(30.0f);
}


void TimetrackUI::OnUpdate(const float& dt)
{
    m_HoverSpellIcon = nullptr;
    for (SpellIconUI* icon : m_Icons)
    {
        if (icon->IsBeingHover())
        {
            m_HoverSpellIcon = icon;
        }
    }
}

void TimetrackUI::SetExpandHighlight(bool doHighLight)
{
    if (doHighLight)
    {
        m_ExpandButton->SetTexture("Sprites/UI/Game/Timeline/ui_game_timeline_button-highlight.png");
    }
    else
    {
        m_ExpandButton->SetTexture("Sprites/UI/Game/Timeline/ui_game_timeline_button.png");
    }
}

void TimetrackUI::SetExpandButtonScale(float scale)
{
    m_ExpandButton->scale.y = scale;
    m_ExpandButton->position.y = (m_Box->scale.y / -2.0f + m_ExpandButton->scale.y / -2.0f);
}

void TimetrackUI::PreviewIcon(CastSpellDetail* spell, bool doCast, bool active)
{
    if (spell != nullptr)
    {
        m_PreviewIcon->SetIcon(spell, doCast);
        m_PreviewIcon->SetIsPreview(true);
    }
    

    // if icon is not active & command say active
    if (!m_PreviewIcon->IsActive() && active)
    {
        if (active)
        {
            m_Icons.push_back(m_PreviewIcon);
        }
    }
    else if(!active)
    {
        auto found = std::find(m_Icons.begin(), m_Icons.end(), m_PreviewIcon) != m_Icons.end();
        if (found)
        {
            m_Icons.pop_back();
        }
    }

    m_PreviewIcon->SetActive(active);

    UpdateTrack();

    bool isTrackFull = BattleManager::GetInstance().Data.Timeline.GetTimetrack(m_TrackIndex)->IsTrackFull(m_PreviewIcon->SpellDetail->SpellOwner) && m_PreviewIcon->IsActive();
    m_PreviewIcon->SetIsExtra(isTrackFull);
    HighlightTrack(!isTrackFull);
}

void TimetrackUI::UpdateTrack()
{
    float newScale = scaleDefault;
    float gap = iconGap;

    bool isOversize = m_Icons.size() > maxIcon;
    int topIconIndex = !isOversize ? 0 : m_Icons.size() - maxIcon;

    for (int i = 0; i < m_Icons.size(); i++)
    {
        auto icon = m_Icons[i];
        int pos = i >= topIconIndex && isOversize && !m_IsExpanded ? i - topIconIndex  : i;

        float offset = (gap * (m_Icons.size() - (i + 1)));
        icon->position.y =-offset;

        if (i >= topIconIndex)
        {
            icon->SetActive(true);
            icon->UpdateIcon();
            icon->SetIsExtra(i == topIconIndex && isOversize);
        }
        else
        {
            icon->SetActive(false);
        }
    }

    m_WillCompareUI->UpdateTextWillValue(m_Icons);

    m_Box->scale.y = newScale;

    m_Box->position.y = (newScale - scaleDefault) / -2.0f;

    SetExpandButtonScale(30.0f);
    SetExpandHighlight(isOversize);

}

void TimetrackUI::AddIcon(CastSpellDetail* spell)
{
    PreviewIcon(spell,false,false);
    auto icon = m_ObjectManager->CreateObject<SpellIconUI>(new SpellIconUI(spell->GetSpellDetail()->GetSpellName() + "_icon", iconSize));

    switch (spell->GetSpellDetail()->GetChannelEffectType())
    {
    case ChannelEffectEnum::None:
    case ChannelEffectEnum::Wait:
        icon->SetIcon(spell, spell->doCast);
        break;
    case ChannelEffectEnum::Active:
    case ChannelEffectEnum::Trap:
    case ChannelEffectEnum::Counter:
        icon->SetIcon(spell, spell->Channel != CastSpellDetail::Head);
        break;
    }

    
    m_IconParent->SetChildRenderBack(icon);
    m_Icons.push_back(icon);

    UpdateTrack();
}
void TimetrackUI::AddIcon(SpellIconUI* spellIcon)
{
    if (spellIcon != m_PreviewIcon)
    {
        m_IconParent->SetChildRenderBack(spellIcon);
    }
    else
    {
        m_IconParent->SetChildRenderFront(spellIcon);
    }
    m_Icons.push_back(spellIcon);

    UpdateTrack();
}

void TimetrackUI::RemoveAllIcon()
{
    m_Icons.clear();
}

void TimetrackUI::RemoveIcon(CastSpellDetail* spell)
{
    auto it = m_Icons.begin();
    for (it = m_Icons.begin(); it != m_Icons.end(); ++it)
    {
        SpellIconUI* iconSpell = *it;
        if (iconSpell-> SpellDetail == spell)
        {
            break;
        }
    }

    if (it != m_Icons.end())
    {
        SpellIconUI* iconSpell = *it;
        m_IconParent->RemoveChild(iconSpell);
        m_Icons.erase(it);
    }

    UpdateTrack();
}

void TimetrackUI::ClearTrack()
{

    for (auto icon : m_Icons)
    {
        m_ObjectManager->DeleteObjectByPointer(icon);
    }
    m_Icons.clear();

    m_WillCompareUI->ResetWillCompareUI();
}


void TimetrackUI::SetIsExpand(bool expand)
{
    m_IsExpanded = expand;
}

void TimetrackUI::HighlightTrack(bool doHighlight)
{
    m_Box->color = doHighlight ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
    m_ExpandButton->color = doHighlight ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
}


SpellIconUI* TimetrackUI::GetHoverSpellIcon() const
{
    return m_HoverSpellIcon;
}
const std::vector<SpellIconUI*>& TimetrackUI::GetSpellDetailUIList() const
{
    return m_Icons;
}
const SpellIconUI* TimetrackUI::GetPreviewIcon() const
{
    return m_PreviewIcon;
}