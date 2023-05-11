#include "SpellDispather.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/GameObject/SpellObject/Earth/EarthSpellObjects.h"
#include "Game/BattleScene/GameObject/SpellObject/Fire/FireSpellObjects.h"
#include "Game/BattleScene/GameObject/SpellObject/Water/WaterSpellObjects.h"
#include "GameObject/SpellObject/Wind/WindSpellObjects.h"

SpellController* SpellDispatcher::SpawnSpell(CastSpellDetail* detail,CasterPosition target)
{
    BaseSpellObject* newSpell = nullptr;
    switch (detail->GetSpellDetail()->m_Element)
    {
    case Element::Earth:
        newSpell = EarthSpellObject::CreateSpellObject(detail->GetSpellDetail()->m_Index, target);
        m_Spells[detail] = m_ObjectManager->CreateObject<BaseSpellObject>(newSpell);
        break;
    case Element::Fire:
        newSpell = FireSpellObject::CreateSpellObject(detail->GetSpellDetail()->m_Index, target);
        m_Spells[detail] = m_ObjectManager->CreateObject<BaseSpellObject>(newSpell);
        break;
    case Element::Water:
        newSpell = WaterSpellObject::CreateSpellObject(detail->GetSpellDetail()->m_Index, target);
        m_Spells[detail] = m_ObjectManager->CreateObject<BaseSpellObject>(newSpell);
        break;
    case Element::Wind:
        newSpell = WindSpellObject::CreateSpellObject(detail->GetSpellDetail()->m_Index, target);
        m_Spells[detail] = m_ObjectManager->CreateObject<BaseSpellObject>(newSpell);
        break;
    }

    return newSpell;
}

void SpellDispatcher::DestroySpell(CastSpellDetail* detail)
{
    // Delete SpellObject
    m_ObjectManager->DeleteObjectByPointer(m_Spells[detail]);

    // Delete SpellObject's Child
    std::vector<GameObject*> deleteChildList = m_Spells[detail]->GetChildList();
    for (int idx = 0; idx < deleteChildList.size(); idx++)
    {
        if(dynamic_cast<ParticleSystem*>(deleteChildList[idx]) != nullptr)
            m_ObjectManager->DeleteObjectByPointer(deleteChildList[idx]);
    }
}

SpellDispatcher::SpellDispatcher():m_ObjectManager(GameStateController::GetInstance().currentScene)
{
}
