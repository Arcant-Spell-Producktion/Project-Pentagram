#pragma once
#include "SpellDatabase.h"

void SpellDatabase::AddSpellBook(string filename)
{
    string path = "Spellbooks/" + filename + ".xml";
    SpellBook newBook(path);
    SpellBooks.emplace(filename, newBook);
    newBook.PrintBookDetail();
}