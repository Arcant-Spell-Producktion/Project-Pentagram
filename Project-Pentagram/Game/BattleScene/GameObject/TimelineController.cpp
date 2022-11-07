#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"
#include "TimelineController.h"

TimelineController::TimelineController():m_ObjectManager(GameStateController::GetInstance()->currentScene), UIObject("TimelineUI")
{
    this->color.a = 0.0f;
    this->position.y += 400.0f;

    top = m_ObjectManager->CreateUIObject("Timeline_UI_Banner");
    top->scale = { 1320.0f,40.0f,1.0f };
    top->position.y += 120.0f;
    top->color.a = 0.0f;
    this->SetChildRenderFront(top);

    trackMarker = m_ObjectManager->CreateUIObject("Timeline_Track_Marker");
    trackMarker->scale = { 20.0f,20.0f,1.0f };
    trackMarker->SetActive(false);
    top->SetChildRenderFront(trackMarker);

    box = m_ObjectManager->CreateUIObject("TimelineUIBOX");
    box->scale = { 1920.0f,280,1.0f };
    box->SetTexture("Sprites/UI/Game/Timeline/ui_game_timeline_header.png");
    this->SetChildRenderBack(box);

    auto bm = BattleManager::GetInstance();
    for (size_t i = 0; i < 11; i++)
    {
        std::function<void()> expandFunc = [this, i]() {ExpandTracks(i); };
        auto track = m_ObjectManager->CreateObject<TimetrackUI>(new TimetrackUI(i, bm->Data.Timeline.GetTimetrack(i), expandFunc));
        m_Tracks.push_back(track);
        box->SetChildRenderFront(track);
    }
}

void TimelineController::SetTrackerActive(bool isActive)
{
    trackMarker->SetActive(isActive);
}

void TimelineController::SetTrackerPositionByIndex(int index)
{
    trackMarker->position.x = index * 120.0f - 600.0f;
}

void TimelineController::ExpandTracks(int TrackIndex)
{
    for (size_t i = 0; i < 11; i++)
    {
        m_Tracks[i]->ExpandTrack(i == TrackIndex);
    }
}

void TimelineController::UpdatePreviewIcon(int time, CastSpellDetail* spell)
{
    int index = time - 1;

    if (index >= 10) index = 10;

    for (size_t i = 0; i < 11; i++)
    {
        m_Tracks[i]->PreviewIcon(i == index, spell);
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
