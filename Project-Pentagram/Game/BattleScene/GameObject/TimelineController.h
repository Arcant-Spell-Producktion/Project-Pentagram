#pragma once
#include "Engine/IGameObjectManager.h"
#include "TimetrackUI.h"
#include "PentagramObject/PentagramController.h"

class TimelineController : public UIObject
{
private:
    IGameObjectManager* m_ObjectManager;

    UIObject* top;
    UIObject* box;

    UIObject* trackMarker;

    UIObject* timelineExpander;
    int currentExpanderIndex;

    std::vector<TimetrackUI*> m_Tracks;

    PentragramController* pentragramControllerRef;

    void ClearTimelineExpander();
    void InsertTimetrackToExpander(int index);

public:
    TimelineController();

    void SetTrackerActive(bool isActive);
    void SetTrackerPositionByIndex(int index);

    void SetPentragramControllerReference(PentragramController* _pentragramControllerRef);

    void SetExpandTimeline(int index, bool doExpand);
    void UpdatePreviewIcon(CastSpellDetail* spell = nullptr);
    void AddIconToTrack(int index, CastSpellDetail* spell);
    void ClearTrack(int index);
    void UpdateAllTracks();
    void ClearAllTrack();
};