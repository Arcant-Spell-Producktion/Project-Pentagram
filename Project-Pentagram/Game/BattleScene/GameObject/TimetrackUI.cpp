#include "Engine/GameStateController.h"
#include "TimetrackUI.h"

TimetrackUI::TimetrackUI(int index):m_Scene(GameStateController::GetInstance()->currentScene), UIObject("TrackUI_"+index)
{
    this->position.y = 440.0f;
    this->position.x = index * 125.0f - 625.0f;
    this->scale = { 125.0f,140.0f,1.0f };
    this->color = AC_RED;

    this->color.a = 0.5f + (0.5f * index / 10.0f);
}

void TimetrackUI::AddIcon(CastSpellDetail* spell)
{
    //std::cout << "ADD ICON 3\n";
    auto icon = m_Scene->CreateObject<SpellIconUI>(new SpellIconUI("WTF"));
    icon->SetDetail(spell);
    icon->position.x = this->position.x;
    icon->position.y = this->position.y + 100.0f* m_Icons.size();
    //this->SetChildRenderFront(icon);
    m_Icons.push_back(icon);
}

void TimetrackUI::ClearTrack()
{
}
