#pragma once
#include "Engine/GameScene.h"
#include "Game/BattleScene/SpellTimeline/SpellTimetrack.h"
#include <Game/BattleScene/GameObject/SpellIconUI.h>

class TimetrackUI : public UIObject
{
private:
    GameScene* m_Scene;

    SpellTimetrack* m_TrackPtr;
    vector<SpellIconUI*> m_Icons;

public:
    TimetrackUI(int index,SpellTimetrack* track);

    void AddIcon(CastSpellDetail* spell);

    void UpdateTrack();

    void ClearTrack();
};