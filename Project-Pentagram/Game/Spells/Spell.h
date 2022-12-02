#pragma once

#include <iostream>
#include <string>
#include "SpellEffectType.h"
#include "ChannelEffectType.h"
#include "Game/Spells/Element.h"

using namespace std;

class Spell
{
private:
    std::string m_Name = "New Spell";
    int m_WillValues[6];
    SpellEffectEnum m_SpellEffectType = SpellEffectEnum::None;
    int m_SpellEffectValues[6] = { 0,0,0,0,0,0 };
    int m_OriginalCastTime = 1;
    ChannelEffectEnum m_ChannelEffectType = ChannelEffectEnum::None;
    int m_ChannelTime = 0;
public:
    Element::Type m_Element;
    int m_Index;

    Spell(Element::Type element = Element::Debug, int index = -1) :
        m_Element(element),
        m_Index(index),
        m_Name("New Spell"),
        m_WillValues{ 0,0,0,0,0,0 },
        m_SpellEffectType(SpellEffectEnum::None),
        m_SpellEffectValues{ 0,0,0,0,0,0 },
        m_OriginalCastTime(1),
        m_ChannelEffectType(ChannelEffectEnum::None),
        m_ChannelTime(0)
    {}

    const int GetSpellIndex() { return m_Index; }
    void SetSpellName(std::string name) { m_Name = name; }
    const std::string GetSpellName() { return m_Name; }

    void SetWillValue(int i, int value) { m_WillValues[i] = value; }
    const int GetWillValue(int i) { return m_WillValues[i]; }

    void SetSpellEffectType(SpellEffectEnum type) { m_SpellEffectType = type; }
    const SpellEffectEnum GetSpellEffectType() { return m_SpellEffectType; }

    void SetSpellEffectValue(int i, int value) { m_SpellEffectValues[i] = value; }
    const int GetSpellEffectValue(int i) { return m_SpellEffectValues[i]; }

    void SetCastTime(int time) { m_OriginalCastTime = time; }
    const int GetCastTime() { return m_OriginalCastTime; }

    void SetChannelEffectType(ChannelEffectEnum type) { m_ChannelEffectType = type; }
    const ChannelEffectEnum GetChannelEffectType() { return m_ChannelEffectType; }

    void SetChannelTime(int time) { m_ChannelTime = time; }
    const int GetChannelTime() { return m_ChannelTime; }

    friend ostream& operator<<(ostream& os, const Spell& dt);
};

