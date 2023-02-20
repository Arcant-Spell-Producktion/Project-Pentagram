#include "SpellDispather.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/GameObject/SpellObject/Fire/FireSpellObjects.h"
#include "Game/BattleScene/GameObject/SpellObject/Water/WaterSpellObjects.h"

SpellController* SpellDispatcher::SpawnSpell(CastSpellDetail* detail,CasterPosition target)
{
    BaseSpellObject* newSpell = nullptr;
    switch (detail->OriginalSpell->m_Element)
    {
    case Element::Earth:
        break;
    case Element::Fire:
        newSpell = FireSpellObject::CreateSpellObject(detail->OriginalSpell->m_Index, target);
        m_Spells[detail] = m_ObjectManager->CreateObject<BaseSpellObject>(newSpell);
        break;
    case Element::Water:
        newSpell = WaterSpellObject::CreateSpellObject(detail->OriginalSpell->m_Index, target);
        m_Spells[detail] = m_ObjectManager->CreateObject<BaseSpellObject>(newSpell);
        break;
    case Element::Wind:
        break;
    }

    return newSpell;
}

void SpellDispatcher::DestroySpell(CastSpellDetail* detail)
{
    m_ObjectManager->DeleteObjectByPointer(m_Spells[detail]);
}

SpellDispatcher::SpellDispatcher():m_ObjectManager(GameStateController::GetInstance()->currentScene)
{
}
