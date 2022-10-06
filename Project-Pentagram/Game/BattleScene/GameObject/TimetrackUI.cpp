#include "Engine/GameStateController.h"
#include "TimetrackUI.h"

TimetrackUI::TimetrackUI(int index,SpellTimetrack* track):m_TrackPtr(track),m_Scene(GameStateController::GetInstance()->currentScene), UIObject("TrackUI_"+index)
{
    this->position.x = index * 125.0f - 625.0f;
    this->scale = { 125.0f,140.0f,1.0f };
    this->color = AC_RED;

    this->color.a = 0.5f + (0.5f * index / 10.0f);
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
}

void TimetrackUI::AddIcon(CastSpellDetail* spell)
{
    auto icon = m_Scene->CreateObject<SpellIconUI>(new SpellIconUI(spell->OriginalSpell->GetSpellName()));
    icon->SetIcon(spell);
    this->SetChildRenderFront(icon);
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
