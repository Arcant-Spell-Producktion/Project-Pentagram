#pragma once
#include <map>
#include "../../Utilities/Singleton.h"
#include "SpellBook.h"

class SpellDatabase:public Singleton<SpellDatabase>
{
public:
    map<string, SpellBook> SpellBooks;

    SpellDatabase();
    void AddSpellBook(string filename);
};