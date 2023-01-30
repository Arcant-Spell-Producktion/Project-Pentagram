#include "Engine/GameStateController.h"
#include "TimetrackUI.h"

const int maxIcon = 7;

const float trackY = 20.0f;

const float trackWidth = 120.0f;

const float scaleDefault = 160.0f;
const float iconSize = 80.0f;
const float iconGap = 20.0f;

std::string TimelineTrackSprite[2] =
{
    "Sprites/UI/Game/Timeline/ui_game_timeline_banner-borderless.png",
    "Sprites/UI/Game/Timeline/ui_game_timeline_banner-border.png"
};

TimetrackUI::TimetrackUI(int index, SpellTimetrack* track, std::function<void()> expand):m_TrackPtr(track),m_ObjectManager(GameStateController::GetInstance()->currentScene), UIObject("TrackUI_" + std::to_string(index))
{
    m_TrackIndex = index;

    this->position.x = m_TrackIndex * trackWidth - (trackWidth * 5);
    this->position.y = trackY;
    this->color.a = 0.0f;

    m_Box = new UIObject("TrackUI_Box_" + std::to_string(m_TrackIndex));
    m_Box->scale = { trackWidth,scaleDefault,1.0f };

    m_IconParent = new UIObject("TrackUI_IconParent_" + std::to_string(m_TrackIndex));
    m_IconParent->color.a = 0.0f;
    m_IconParent->position.y += 35.0f;

    m_Box->SetTexture(TimelineTrackSprite[0]);
    m_Box->SetIsSlicing(true);
    m_Box->SetSlicingBorderSize(50.0f);
    m_Box->SetSlicingBorderMultiplier(0.4f);
    m_Box->SetSlicingType(SlicingType::REPEAT);


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
        expand();

        auto index = m_ExpandButton->GetCurrentAnimationIndex();
        m_ExpandButton->SetSpriteByIndex((index.x + 1)%2, 0);
    };

    this->SetChildRenderBack(m_Box);
    this->SetChildRenderFront(m_IconParent);
    m_IconParent->SetChildRenderFront(m_PreviewIcon);
    m_Box->SetChildRenderFront(m_ExpandButton);

    SetExpandButtonScale(30.0f);
}

void TimetrackUI::SetExpandButtonScale(float scale)
{
    m_ExpandButton->scale.y = scale;
    m_ExpandButton->position.y = (m_Box->scale.y / -2.0f + m_ExpandButton->scale.y / -2.0f);
}

void TimetrackUI::ExpandTrack(bool isExpand)
{
    std::cout << "EXPAND" << m_TrackIndex << ": " << isExpand << "\n";
    m_IsExpanded = !m_IsExpanded && isExpand;
    UpdateTrack();
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

    UpdateTrack();
    m_PreviewIcon->SetActive(active);

}

void TimetrackUI::UpdateTrack()
{
    float newScale = scaleDefault;
    float gap = iconGap;

    bool isOversize = m_Icons.size() > maxIcon;
    int topIconIndex = !isOversize ? 0 : m_Icons.size() - maxIcon;

    if (!m_IsExpanded)
    {
        switch (m_Icons.size())
        {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            newScale += 30.0f;
            break;
        case 5:
            newScale += 50.0f;
            break;
        case 6:
        default:
            newScale += 80.0f;
            break;
        }

    }
    else
    {
        //calulate gap
        switch (m_Icons.size())
        {
        case 11:
        case 12:
            gap = 75.0f;
            break;
        case 13:
            gap = 69.5f;
            break;
        case 14:
            gap = 65.0f;
            break;
        case 15:
            gap = 60.5f;
            break;
        case 16:
            gap = 57.0f;
            break;
        case 17:
            gap = 54.0f;
            break;
        case 18:
            gap = 51.0f;
            break;
        case 19:
            gap = 48.5f;
            break;
        case 20:
            gap = 46.5f;
            break;
        default:
            gap = 80.0f;
            break;
        }

        //calculate banner size
        if (m_Icons.size() >= 2)
            {
                newScale += 40.0f;

                int x = m_Icons.size() - 2;
                x = x < 10 ? x : 10;
                newScale += 80.0f * x;

            }
         
        std::cout << m_Icons.size() << " " << gap << " " << newScale << "\n";
        
    }

    for (int i = 0; i < m_Icons.size(); i++)
    {
        auto icon = m_Icons[i];
        int pos = i >= topIconIndex && isOversize && !m_IsExpanded ? i - topIconIndex  : i;

        float offset = (gap * (m_Icons.size() - (i + 1)));
        icon->position.y =-offset;

        if (i >= topIconIndex || m_IsExpanded)
        {
            icon->SetActive(true);
            icon->UpdateIcon();
            icon->SetIsExtra(i == topIconIndex && isOversize && !m_IsExpanded);
        }
        else
        {
            icon->SetActive(false);
        }
    }

    m_Box->scale.y = newScale;

    m_Box->position.y = (newScale - scaleDefault) / -2.0f;

    SetExpandButtonScale(30.0f);
}

void TimetrackUI::AddIcon(CastSpellDetail* spell)
{
    PreviewIcon(spell,false,false);
    auto icon = m_ObjectManager->CreateObject<SpellIconUI>(new SpellIconUI(spell->OriginalSpell->GetSpellName() + "_icon", iconSize));
    icon->SetIcon(spell, spell->doCast);
    m_IconParent->SetChildRenderBack(icon);
    m_Icons.push_back(icon);

    UpdateTrack();
}

void TimetrackUI::ClearTrack()
{
    for (auto icon : m_Icons)
    {
        m_ObjectManager->DeleteObjectByPointer(icon);
    }
    m_Icons.clear();
}
