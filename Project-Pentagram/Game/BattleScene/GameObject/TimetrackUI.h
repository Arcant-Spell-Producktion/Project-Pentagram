#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellTimeline/SpellTimetrack.h"
#include <Game/BattleScene/GameObject/SpellIconUI.h>
#include "Game/BattleScene/GameObject/WillCompareUI.h"

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

    WillCompareUI* m_WillCompareUI;

    SpellIconUI* m_HoverSpellIcon;

    void SetExpandHighlight(bool doHighLight);
    void SetExpandButtonScale(float scale);

public:

    TimetrackUI(int index,SpellTimetrack* track, std::function<void(bool doExpand)> expand);

    void OnUpdate(const float& dt) override;

    void PreviewIcon(CastSpellDetail* spell = nullptr, bool doCast = false ,bool active = false);

    void AddIcon(CastSpellDetail* spell);
    void AddIcon(SpellIconUI* spellIcon);

    void RemoveIcon(CastSpellDetail* spell);

    void ExpandTrack(bool isExpand);
    void RemoveAllIcon();

    void UpdateTrack();

    void ClearTrack();

    void SetIsExpand(bool expand);

    void HighlightTrack(bool doHighlight);

    SpellIconUI* GetHoverSpellIcon() const;
    const std::vector<SpellIconUI*>& GetSpellDetailUIList() const;
    const SpellIconUI* GetPreviewIcon() const;
};