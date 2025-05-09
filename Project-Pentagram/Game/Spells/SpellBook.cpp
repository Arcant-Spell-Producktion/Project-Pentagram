﻿#pragma once

#include "SpellBook.h"
#include "Utilities/TinyXml/tinyxml2.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace tinyxml2;

SpellBook::SpellBook(Element::Type element, std::string filename) :m_Element(element),m_Bookname(filename)
{
    std::string path = "Spellbooks/" + filename + ".xml";
    XMLDocument doc;
    doc.LoadFile(path.c_str());

    XMLElement* SpellList = doc.FirstChildElement("SpellBook")->FirstChildElement("SpellList");
    XMLElement* currSpellElement = SpellList->FirstChildElement("Spell");
    for (int spell_index = 0; spell_index < 9; spell_index++)
    {
        Spell currSpell(element, spell_index);

        XMLElement* castTimeElement = currSpellElement->FirstChildElement("CastTime");
        XMLElement* channelTimeElement = currSpellElement->FirstChildElement("ChannelTime");
        XMLElement* effectTypeElement = currSpellElement->FirstChildElement("SpellEffect");
        XMLElement* channelTypeElement = currSpellElement->FirstChildElement("ChannelEffect");
        XMLElement* willValueElement = currSpellElement->FirstChildElement("WillValue")->FirstChildElement("Value");
        XMLElement* effectValueElement = currSpellElement->FirstChildElement("EffectValue")->FirstChildElement("Value");
        XMLElement* targetElement = currSpellElement->FirstChildElement("SpellTarget");
        XMLElement* resolveFlagElement = currSpellElement->FirstChildElement("ResolveFlag");


        currSpell.SetSpellName(currSpellElement->FirstAttribute()->Value());

        currSpell.SetCastTime(std::stoi(castTimeElement->GetText()));

        currSpell.SetChannelTime(std::stoi(channelTimeElement->GetText()));

        currSpell.SetSpellTarget(SpellTargetType::GetEnum(targetElement->GetText()));

        currSpell.SetSpellEffectType(SpellEffectType::GetEnum(effectTypeElement->GetText()));

        currSpell.SetChannelEffectType(ChannelEffectType::GetEnum(channelTypeElement->GetText()));

        for (int array_index = 0; array_index < 6; array_index++)
        {
            currSpell.SetWillValue(array_index, std::stoi(willValueElement->GetText()));
            currSpell.SetSpellEffectValue(array_index, std::stoi(effectValueElement->GetText()));

            willValueElement = willValueElement->NextSiblingElement();
            effectValueElement = effectValueElement->NextSiblingElement();
        }

        currSpell.SetResolveEffectFlag(std::stoi(resolveFlagElement->GetText()));

        AddNewSpell(currSpell);

        currSpellElement = currSpellElement->NextSiblingElement();
    }
}

void SpellBook::PrintBookDetail() {
    std::cout << "\n\t Book Name: " << m_Bookname << "\n\n";
    for (int i = 0; i < 9; i++)
    {
        std::cout << "\t Spell Numero: " << i << "\n" << m_Spells[i] <<"\n";
    }
}
