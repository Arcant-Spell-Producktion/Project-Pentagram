#pragma once
#include "SpellDatabase.h"

SpellDatabase::SpellDatabase()
{
    AddSpellBook(Element::Debug,"Ligma");
}

void SpellDatabase::AddSpellBook(Element::Type element , string filename)
{
    SpellBook newBook(element,filename);
    SpellBooks.emplace(element, newBook);
    newBook.PrintBookDetail();
}
