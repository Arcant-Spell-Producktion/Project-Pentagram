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
    UIObject* m_IconParent;
    SpellTimetrack* m_TrackPtr;
    std::vector<SpellIconUI*> m_Icons;
    SpellIconUI* m_PreviewIcon;

    Button* m_ExpandButton;

    bool m_IsExpanded = false;

    void SetExpandButtonScale(float scale);

public:

    TimetrackUI(int index,SpellTimetrack* track, std::function<void()> expand);

    void PreviewIcon(CastSpellDetail* spell = nullptr, bool doCast = false ,bool active = false);

    void AddIcon(CastSpellDetail* spell);

    void RemoveIcon(CastSpellDetail* spell);

    void ExpandTrack(bool isExpand);

    void UpdateTrack();

    void ClearTrack();
};