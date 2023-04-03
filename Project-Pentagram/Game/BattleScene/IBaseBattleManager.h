#pragma once
#include "Game/BattleScene/BattleSceneData.h"

class IBaseBattleManager
{
public:
    BattleSceneData Data;

    virtual void UpdateDisplaySpellDetail(CasterPosition position, CastSpellDetail* spell = nullptr, bool isMainData = false, glm::vec3 IconPos = { 0,0,0 }) = 0;
};