#include "Engine/GameStateController.h"
#include "TimetrackUI.h"

const int maxIcon = 7;

const float trackWidth = 120.0f;

const float scaleDefault = 140.0f;
const float iconGap = 20.0f;



TimetrackUI::TimetrackUI(int index,SpellTimetrack* track, std::function<void()> expand):m_TrackPtr(track),m_ObjectManager(GameStateController::GetInstance()->currentScene), UIObject("TrackUI_"+index)
{
    m_TrackIndex = index;

    this->position.x = m_TrackIndex * trackWidth - (trackWidth * 5);
    this->color.a = 0.0f;

    m_Box = m_ObjectManager->CreateUIObject("TrackUI_Box_" + m_TrackIndex);
    m_Box->scale = { trackWidth,scaleDefault,1.0f };
    m_Box->color = AC_RED;
    m_Box->color.a = 0.5f + (0.5f * m_TrackIndex / 10.0f);
    this->SetChildRenderBack(m_Box);

    m_PreviewIcon = m_ObjectManager->CreateObject<SpellIconUI>(new SpellIconUI("PreviewIcon_"+ m_TrackIndex));
    m_PreviewIcon->SetActive(false);
    this->SetChildRenderFront(m_PreviewIcon);

    m_ExpandButton = m_ObjectManager->CreateButton("Expand_" + m_TrackIndex);
    m_ExpandButton->scale = { trackWidth , 30.0f , 1.0f };

    m_ExpandButton->onHover = [this](Button* button)
    {
        m_ExpandButton->color = { 0.5f,0.5f ,0.5f ,0.5f };
        SetExpandButtonScale(60.0f);
    };

    m_ExpandButton->unHover = [this](Button* button)
    {
        m_ExpandButton->color = AC_WHITE;
        SetExpandButtonScale(30.0f);
    };

    m_ExpandButton->onClick = [this, expand](Button* button)
    {
        std::cout << "TRY EXPAND" << m_TrackIndex << "\n";
        expand();
    };

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

void TimetrackUI::PreviewIcon(bool active, CastSpellDetail* spell = nullptr)
{
    static int previewPosition;
    if (spell != nullptr) m_PreviewIcon->SetIcon(spell);
    
    if (!m_PreviewIcon->IsActive() && active)
    {
        if (active)
        {
            if (m_Icons.size() > maxIcon)
            {
                m_Icons.insert(m_Icons.begin() + maxIcon, m_PreviewIcon);
            }
            else
            {
                m_Icons.push_back(m_PreviewIcon);
            }
        }
    }
    else
    {
        auto found = std::find(m_Icons.begin(), m_Icons.end(), m_PreviewIcon) != m_Icons.end();
        if (found)
        {
            if (m_Icons.size() > maxIcon)
            {
                m_Icons.erase(m_Icons.begin() + maxIcon);
            }
            else
            {
                m_Icons.pop_back();
            }
        }
    }

    UpdateTrack();
    m_PreviewIcon->SetActive(active);

}

void TimetrackUI::UpdateTrack()
{
    float newScale = scaleDefault;

    if (!m_IsExpanded)
    {
        m_PreviewIcon->SetTransparency(true);

        if (m_Icons.size() > maxIcon)
        {
            m_Icons[maxIcon-1]->SetIconType(IconType::Extra);
        }

        for (int i = 0; i < m_Icons.size(); i++)
        {
            auto icon = m_Icons[i];
            icon->position.y = -iconGap * (i - 1);
            if (i < maxIcon)
            {
                icon->UpdateIcon();
            }
            else
            {
                icon->SetActive(false);
            }
        }

        switch (m_Icons.size())
        {
        case 0:
        case 1:
        case 2:
           break;
        case 3:
            newScale += 10.0f;
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
        int i = 0;
        for (auto icon : m_Icons)
        {
            icon->position.y = -100.0f * i;
            icon->UpdateIcon();
            i++;
        }
        newScale += m_Icons.size() * 100.0f;
    }

    m_Box->scale.y = newScale;

    m_Box->position.y = (newScale - scaleDefault) / -2.0f;
    
}

void TimetrackUI::AddIcon(CastSpellDetail* spell)
{
    PreviewIcon(false);
    auto icon = m_ObjectManager->CreateObject<SpellIconUI>(new SpellIconUI(spell->OriginalSpell->GetSpellName()));
    icon->SetIcon(spell);
    this->SetChildRenderBack(icon);
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
