#pragma once
#include <map>
#include "../../Utilities/Singleton.h"
#include "SpellBook.h"

class SpellDatabase:public Singleton<SpellDatabase>
{
public:
    map<Element::Type, SpellBook*> SpellBooks;

    SpellDatabase();
    void AddSpellBook(Element::Type element, string filename);
    SpellBook* GetBookByElement(Element::Type element)
    {
     return SpellBooks.find(element)->second;
    }
};