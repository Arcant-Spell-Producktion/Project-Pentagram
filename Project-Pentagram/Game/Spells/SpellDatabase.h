#pragma once
#include "SpellBook.h"

class SpellDatabase
{
public:
    map<string, SpellBook> SpellBooks;
    void AddSpellBook(string filename);
};