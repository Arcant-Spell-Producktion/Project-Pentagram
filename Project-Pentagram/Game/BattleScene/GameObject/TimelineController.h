#pragma once
#include "Engine/GameScene.h"
#include "TimetrackUI.h"

class TimelineController : public UIObject
{
private:
    GameScene* m_Scene;

    UIObject* box;
    vector<TimetrackUI*> m_Tracks;
public:
    TimelineController();

    void AddIconToTrack(int index, CastSpellDetail* spell);
    void ClearTrack(int index);
    void UpdateAllTracks();
    void ClearAllTrack();
};