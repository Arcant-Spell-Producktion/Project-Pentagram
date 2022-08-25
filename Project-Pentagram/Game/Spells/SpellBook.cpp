#pragma once

#include "SpellBook.h"
#include "../../Utilities/TinyXml/tinyxml2.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace tinyxml2;

SpellBook::SpellBook(string path)
{
    XMLDocument doc;
    doc.LoadFile(path.c_str());

    XMLElement* SpellList = doc.FirstChildElement("SpellBook")->FirstChildElement("SpellList");
    XMLElement* currSpellElement = SpellList->FirstChildElement("Spell");
    for (int spell_index = 0; spell_index < 9; spell_index++)
    {
        Spell currSpell;

        XMLElement* castTimeElement = currSpellElement->FirstChildElement("CastTime");
        XMLElement* channelTimeElement = currSpellElement->FirstChildElement("ChannelTime");
        XMLElement* effectTypeElement = currSpellElement->FirstChildElement("SideEffect");
        XMLElement* channelTypeElement = currSpellElement->FirstChildElement("ChannelEffect");
        XMLElement* willValueElement = currSpellElement->FirstChildElement("WillValue")->FirstChildElement("Value");
        XMLElement* effectValueElement = currSpellElement->FirstChildElement("EffectValue")->FirstChildElement("Value");

        currSpell.SetSpellName(currSpellElement->FirstAttribute()->Value());
        currSpell.SetCastTime(int(castTimeElement->GetText()));
        currSpell.SetChannelTime(int(channelTimeElement->GetText()));
        currSpell.SetSideEffectType(SideEffectType::GetEnum(effectTypeElement->GetText()));
        currSpell.SetChannelEffectType(ChannelEffectType::GetEnum(channelTypeElement->GetText()));
        for (int array_index = 0; array_index < 6; array_index++)
        {
            currSpell.SetWillValue(array_index, int(willValueElement->GetText()));
            currSpell.SetSideEffectValue(array_index, int(effectValueElement->GetText()));

            willValueElement = willValueElement->NextSiblingElement();
            effectValueElement = effectValueElement->NextSiblingElement();
        }

        AddNewSpell(currSpell);

        currSpellElement = currSpellElement->NextSiblingElement();
    }
}

void SpellBook::PrintBookDetail() {}
