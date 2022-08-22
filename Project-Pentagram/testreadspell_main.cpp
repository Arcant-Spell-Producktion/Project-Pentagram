#include "Utilities/TinyXml/tinyxml2.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace tinyxml2;
using namespace std;

void PrintArrayElement(XMLElement* arrayElem, int count = 0, string elemName = "")
{
    XMLElement* currValue = arrayElem->FirstChildElement("Value");
    for (int i = 0; i < count; i++)
    {
        cout << "\t\t" << elemName << i << ": " << currValue->GetText() << endl;
        currValue = currValue->NextSiblingElement();
    }
}

void PrintSpellDetail(XMLElement* spell, int i = 0)
{
    cout << spell->FirstAttribute()->Value() << " " << i << endl;
    cout << "\tWill" << endl;
    PrintArrayElement(spell->FirstChildElement("WillValue"), 6, "Dmg");
    cout << "\tSideEffect: " << spell->FirstChildElement("SideEffect")->GetText() << endl;
    cout << "\tEffect" << endl;
    PrintArrayElement(spell->FirstChildElement("EffectValue"), 6, "Eff");
    cout << "\tCastTime: " << spell->FirstChildElement("CastTime")->GetText() << endl;
    cout << "\tChannelTime: " << spell->FirstChildElement("ChannelTime")->GetText() << endl;
    cout << "\tChannelEffect: " << spell->FirstChildElement("ChannelEffect")->GetText() << endl;
}

int main2()
{
    XMLDocument doc;
    doc.LoadFile("Spellbooks/Ligma.xml");

    XMLElement* SpellList = doc.FirstChildElement("SpellBook")->FirstChildElement("SpellList");
    XMLElement* currSpell = SpellList->FirstChildElement("Spell");
    for (int i = 0; i < 9; i++)
    {
        PrintSpellDetail(currSpell, i + 1);
        cout << endl;
        currSpell = currSpell->NextSiblingElement();
    }

    exit(EXIT_SUCCESS);
}