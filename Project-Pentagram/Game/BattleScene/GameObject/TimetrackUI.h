#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellTimeline/SpellTimetrack.h"
#include <Game/BattleScene/GameObject/SpellIconUI.h>

class TimetrackUI : public UIObject
{
private:
    int m_TrackIndex;

    IGameObjectManager* m_ObjectManager;

    UIObject* m_Box;
    SpellTimetrack* m_TrackPtr;
    vector<SpellIconUI*> m_Icons;
    SpellIconUI* m_PreviewIcon;

    Button* m_ExpandButton;

    bool m_IsExpanded = false;

    void SetExpandButtonScale(float scale);

public:

    TimetrackUI(int index,SpellTimetrack* track, std::function<void()> expand);

    void PreviewIcon(bool active, CastSpellDetail* spell);

    void AddIcon(CastSpellDetail* spell);

    void ExpandTrack(bool isExpand);

    void UpdateTrack();

    void ClearTrack();
};