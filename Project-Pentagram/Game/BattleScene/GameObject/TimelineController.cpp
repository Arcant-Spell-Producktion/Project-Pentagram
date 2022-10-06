#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"
#include "TimelineController.h"

TimelineController::TimelineController():m_Scene(GameStateController::GetInstance()->currentScene), UIObject("TimelineUI")
{
    this->color.a = 0.0f;
    this->position.y += 440.0f;

    box = m_Scene->CreateUIObject("TimelineUIBOX");
    box->scale = { 1920.0f,360.0f,1.0f };
    box->color.a = 0.5f;
    this->SetChildRenderBack(box);

    auto bm = BattleManager::GetInstance();
    for (size_t i = 0; i < 11; i++)
    {
        auto track = m_Scene->CreateObject<TimetrackUI>(new TimetrackUI(i,bm->Data.Timeline.GetTimetrack(i)));
        m_Tracks.push_back(track);
        box->SetChildRenderFront(track);
    }
}

void TimelineController::AddIconToTrack(int index, CastSpellDetail* spell)
{
    std::cout << "ADD ICON 2\n";
	m_Tracks[index]->AddIcon(spell);
}

void TimelineController::ClearTrack(int index)
{
    m_Tracks[index]->ClearTrack();
}

void TimelineController::UpdateAllTracks()
{
    for (TimetrackUI* track : m_Tracks)
    {
        track->UpdateTrack();
    }
}

void TimelineController::ClearAllTrack()
{
    for (TimetrackUI* track: m_Tracks)
    {
        track->ClearTrack();
    }
}
