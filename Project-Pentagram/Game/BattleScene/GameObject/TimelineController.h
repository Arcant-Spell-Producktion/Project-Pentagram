#pragma once
#include "Engine/IGameObjectManager.h"
#include "TimetrackUI.h"

class TimelineController : public UIObject
{
private:
    IGameObjectManager* m_ObjectManager;

    UIObject* box;
    vector<TimetrackUI*> m_Tracks;
public:
    TimelineController();

    void UpdatePreviewIcon(int index, CastSpellDetail* spell = nullptr);
    void AddIconToTrack(int index, CastSpellDetail* spell);
    void ClearTrack(int index);
    void UpdateAllTracks();
    void ClearAllTrack();
};