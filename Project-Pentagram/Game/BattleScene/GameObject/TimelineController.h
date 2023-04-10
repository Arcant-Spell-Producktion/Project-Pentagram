#pragma once
#include "Engine/IGameObjectManager.h"
#include "TimetrackUI.h"
#include "PentagramObject/PentagramController.h"
#include "Game/BattleScene/BattleStates/BattleState.h"

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

    SpellDetailUI* m_SpellDetailUI;

    PentragramController* pentragramControllerRef;
    BattleState currentState;

    void ClearTimelineExpander();
    void InsertTimetrackToExpander(int index);

public:
    TimelineController();

    void OnUpdate(const float& dt) override;

    void SetTrackerActive(bool isActive);
    void SetTrackerPositionByIndex(int index);

    void SetPentragramControllerReference(PentragramController* _pentragramControllerRef);
    void SetCurrentState(BattleState state);

    void SetExpandTimeline(int index, bool doExpand);
    void UpdatePreviewIcon(CastSpellDetail* spell = nullptr);
    void AddIconToTrack(int index, CastSpellDetail* spell);
    void RemoveIconFromTrack(int index, CastSpellDetail* spell);
    void ClearTrack(int index);
    void UpdateAllTracks();
    void ClearAllTrack();
};