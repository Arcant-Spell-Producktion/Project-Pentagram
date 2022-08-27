#pragma once
#include "../../Utilities/Singleton.h"
#include "../Spells/SpellDatabase.h"
#include "CastSpellDetail.h"
#include "PentagramData.h"
class SpellCasterController:Singleton<SpellCasterController>
{
private:
    void UpdateCurrentSpell();
protected:
    Caster m_SpellCaster = Caster::NONE;
    bool m_isInit = false;
    Element::Type m_Element = Element::NULLTYPE;
    PentagramData m_PentagramData;
    SpellBook* m_CurrentBook = nullptr;
    CastSpellDetail* m_CurrentSpell = nullptr;
public:
    void Init(Element::Type element,Caster caster);
    virtual void SetPentagramData(PentagramData pentagram);
    void CommitSpell();
    int GetSpellCost();
};

