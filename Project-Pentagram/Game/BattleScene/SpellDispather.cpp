#include "SpellDispather.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/GameObject/SpellObject/Fire/FireSpellObjects.h"

SpellController* SpellDispatcher::SpawnSpell(CastSpellDetail* detail,CasterPosition target)
{
    BaseSpellObject* newSpell;
    switch (detail->OriginalSpell->m_Element)
    {
    case Element::Earth:
        break;
    case Element::Fire:
        newSpell = FireSpellObject::CreateSpellObject(detail->OriginalSpell->m_Index, target);
        m_Spells.emplace(detail, m_ObjectManager->CreateObject<BaseSpellObject>(newSpell));
        break;
    case Element::Water:
        break;
    case Element::Wind:
        break;
    }

    
    return m_Spells[detail];
}

void SpellDispatcher::DestroySpell(CastSpellDetail* detail)
{
    m_ObjectManager->DeleteObjectByPointer(m_Spells[detail]);
}

SpellDispatcher::SpellDispatcher():m_ObjectManager(GameStateController::GetInstance()->currentScene)
{
}
