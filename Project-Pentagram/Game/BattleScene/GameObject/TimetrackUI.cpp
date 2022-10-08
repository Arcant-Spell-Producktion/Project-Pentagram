#include "Engine/GameStateController.h"
#include "TimetrackUI.h"

TimetrackUI::TimetrackUI(int index,SpellTimetrack* track):m_TrackPtr(track),m_Scene(GameStateController::GetInstance()->currentScene), UIObject("TrackUI_"+index)
{
    this->position.x = index * 125.0f - 625.0f;
    this->color.a = 0.0f;

    m_Box = m_Scene->CreateUIObject("TrackUI_Box_" + index);
    m_Box->scale = { 125.0f,140.0f,1.0f };
    m_Box->color = AC_RED;
    m_Box->color.a = 0.5f + (0.5f * index / 10.0f);
    this->SetChildRenderBack(m_Box);

    m_PreviewIcon = m_Scene->CreateObject<SpellIconUI>(new SpellIconUI("PreviewIcon_"+index));
    m_PreviewIcon->SetActive(false);
    this->SetChildRenderFront(m_PreviewIcon);
}

void TimetrackUI::PreviewIcon(bool active, CastSpellDetail* spell = nullptr)
{
    if (spell != nullptr) m_PreviewIcon->SetIcon(spell);
    
    if (!m_PreviewIcon->IsActive() && active)
    {
        if (active)
        {
            m_Icons.push_back(m_PreviewIcon);
        }
    }
    else
    {
        if (std::find(m_Icons.begin(), m_Icons.end(), m_PreviewIcon) != m_Icons.end())
        {
            m_Icons.pop_back();
        }
    }

    m_PreviewIcon->SetActive(active);
    UpdateTrack();

}

void TimetrackUI::UpdateTrack()
{
    int i = 0;
    for (auto icon : m_Icons)
    {
        icon->position.y = -50.0f * i;
        icon->UpdateIcon();
        i++;
    }
    m_PreviewIcon->SetTransparency(true);
}

void TimetrackUI::AddIcon(CastSpellDetail* spell)
{
    PreviewIcon(false);
    auto icon = m_Scene->CreateObject<SpellIconUI>(new SpellIconUI(spell->OriginalSpell->GetSpellName()));
    icon->SetIcon(spell);
    this->SetChildRenderBack(icon);
    m_Icons.push_back(icon);

    UpdateTrack();
}

void TimetrackUI::ClearTrack()
{
    for (auto icon : m_Icons)
    {
        m_Scene->DeleteObjectByPointer(icon);
    }
    m_Icons.clear();
}
