#pragma once
#include <map>
#include "Utilities/Singleton.h"
#include "SpellBook.h"
#include <iostream>

class SpellDatabase:public Singleton<SpellDatabase>
{
    void AddSpellBook(Element::Type element, std::string filename);
public:
    std::map<Element::Type, SpellBook*> SpellBooks;

    void LoadResource();

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