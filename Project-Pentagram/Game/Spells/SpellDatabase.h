#pragma once
#include <map>
#include "Utilities/Singleton.h"
#include "SpellBook.h"

class SpellDatabase:public Singleton<SpellDatabase>
{
    void AddSpellBook(Element::Type element, string filename);
public:
    map<Element::Type, SpellBook*> SpellBooks;

    SpellDatabase();

    SpellBook* GetBookByElement(Element::Type element)
    {
     return SpellBooks.find(element)->second;
    }

    ~SpellDatabase()
    {
        for (auto spellbookPair : SpellBooks)
        {
            delete spellbookPair.second;
        }
        SpellBooks.clear();
    }
};