#pragma once
#include "Engine/IGameObjectManager.h"
#include "TimetrackUI.h"

class TimelineController : public UIObject
{
private:
    IGameObjectManager* m_ObjectManager;

    UIObject* top;
    UIObject* box;

    UIObject* trackMarker;

    vector<TimetrackUI*> m_Tracks;
public:
    TimelineController();

    void SetTrackerActive(bool isActive);
    void SetTrackerPositionByIndex(int index);

    void ExpandTracks(int TrackIndex);
    void UpdatePreviewIcon(CastSpellDetail* spell = nullptr);
    void AddIconToTrack(int index, CastSpellDetail* spell);
    void ClearTrack(int index);
    void UpdateAllTracks();
    void ClearAllTrack();
};