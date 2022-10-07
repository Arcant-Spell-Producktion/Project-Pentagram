#pragma once
#include "SpellDatabase.h"

void SpellDatabase::LoadResource()
{
    AddSpellBook(Element::Fire, "Spellbook_Fire");
    AddSpellBook(Element::Debug,"Ligma");
}

void SpellDatabase::AddSpellBook(Element::Type element , string filename)
{
    SpellBook* newBook = new SpellBook(element,filename);
    SpellBooks.emplace(element, newBook);
    newBook->PrintBookDetail();
}
