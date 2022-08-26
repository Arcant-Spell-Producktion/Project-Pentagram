#pragma once
#include "SpellDatabase.h"

SpellDatabase::SpellDatabase()
{
    AddSpellBook("Ligma");
}

void SpellDatabase::AddSpellBook(string filename)
{
    SpellBook newBook(filename);
    SpellBooks.emplace(filename, newBook);
    newBook.PrintBookDetail();
}
