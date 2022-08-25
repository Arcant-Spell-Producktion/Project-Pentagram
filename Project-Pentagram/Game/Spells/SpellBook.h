#pragma once
#include "Spell.h"

class SpellBook
{
private:
    Spell m_Spells[9];
    int m_Count = 0;
public:
    SpellBook(std::string path);
    void AddNewSpell(Spell newSpell) { m_Spells[m_Count++] = newSpell; }
    Spell GetSpell(int index) { return m_Spells[index]; }
    void PrintBookDetail();
};
