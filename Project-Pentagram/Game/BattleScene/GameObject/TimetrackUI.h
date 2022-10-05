#pragma once
#include "Engine/GameScene.h"
#include <Game/BattleScene/GameObject/SpellIconUI.h>

class TimetrackUI : public UIObject
{
private:
    GameScene* m_Scene;
    vector<SpellIconUI*> m_Icons;
public:
    TimetrackUI(int index);

    void AddIcon(CastSpellDetail* spell);

    void ClearTrack();
};