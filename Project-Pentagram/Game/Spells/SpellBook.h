#pragma once
#include "Spell.h"
#include "Element.h"

class SpellBook
{
private:
    Element::Type m_Element;
    string m_Bookname;
    Spell m_Spells[9];
    int m_Count = 0;
public:
    SpellBook(Element::Type element,std::string filename);
    void AddNewSpell(Spell newSpell) { m_Spells[m_Count++] = newSpell; }
    Spell* GetSpellByIndex(int index) { return &m_Spells[index]; }
    void PrintBookDetail();
};
