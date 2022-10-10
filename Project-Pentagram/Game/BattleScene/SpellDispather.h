#pragma once
#include <map>
#include "Engine/GameScene.h"
#include "Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h"
#include "Game/BattleScene/SpellCaster/CastSpellDetail.h"

class SpellDispatcher
{
private:
    std::map<CastSpellDetail* ,BaseSpellObject*> m_Spells;

    GameScene* m_ObjectManager;
public:
    SpellController* SpawnSpell(CastSpellDetail* detail, CasterPosition target);
    void DestroySpell(CastSpellDetail* detail);

    SpellDispatcher();
};