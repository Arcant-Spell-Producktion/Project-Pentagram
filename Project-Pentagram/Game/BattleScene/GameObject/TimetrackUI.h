#pragma once
#include "Engine/GameScene.h"
#include "Game/BattleScene/SpellTimeline/SpellTimetrack.h"
#include <Game/BattleScene/GameObject/SpellIconUI.h>

class TimetrackUI : public UIObject
{
private:
    GameScene* m_Scene;

    UIObject* m_Box;
    SpellTimetrack* m_TrackPtr;
    vector<SpellIconUI*> m_Icons;
    SpellIconUI* m_PreviewIcon;

public:
    TimetrackUI(int index,SpellTimetrack* track);

    void PreviewIcon(bool active, CastSpellDetail* spell);

    void AddIcon(CastSpellDetail* spell);

    void UpdateTrack();

    void ClearTrack();
};