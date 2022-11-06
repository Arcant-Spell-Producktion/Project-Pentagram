#pragma once
#include "SpellDatabase.h"

void SpellDatabase::LoadResource()
{
    AddSpellBook(Element::Fire, "Spellbook_Fire");
    AddSpellBook(Element::Water, "Spellbook_Water");

    /*TODO::Add 2 other element
    AddSpellBook(Element::Earth, "Spellbook_Earth");
    AddSpellBook(Element::Wind, "Spellbook_Wind");
    */

    //AddSpellBook(Element::Debug,"Ligma");
}

void SpellDatabase::AddSpellBook(Element::Type element , string filename)
{
    SpellBook* newBook = new SpellBook(element,filename);
    SpellBooks.emplace(element, newBook);
    newBook->PrintBookDetail();
}
