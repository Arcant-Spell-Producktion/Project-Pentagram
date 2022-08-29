#pragma once
#include "../../../Utilities/Singleton.h"
#include "../../Spells/SpellDatabase.h"
#include "CastSpellDetail.h"
#include "PentagramData.h"
class SpellCaster:public Singleton<SpellCaster>
{
private:
    void UpdateCurrentSpell();
protected:
    Caster m_SpellCaster = Caster::NONE;
    Element::Type m_Element = Element::NULLTYPE;
    PentagramData_T m_PentagramData;
    SpellBook* m_CurrentBook;
    CastSpellDetail* m_CurrentSpell = nullptr;
public:
    void Init() {};
    void SetUp(Element::Type element,Caster caster);
    void SetPentagramData(PentagramData_T pentagram);
    void CommitSpell();
    int GetSpellCost();
    const CastSpellDetail* GetSpellDetail() {return m_CurrentSpell;}
};

