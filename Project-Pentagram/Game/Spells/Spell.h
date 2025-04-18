#pragma once

#include <iostream>
#include <string>
#include "SpellEffectType.h"
#include "ChannelEffectType.h"
#include "SpellTarget.h"
#include "SpellResolveEffect.h"
#include "Game/Spells/Element.h"

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
    SpellTargetEnum m_SpellTarget = SpellTargetEnum::Opponent;
    SpellResolveEffect m_SpellResolveEffect = 1;
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

    int GetSpellIndex() const { return m_Index; }
    void SetSpellName(std::string name) { m_Name = name; }
    std::string GetSpellName() const { return m_Name; }

    void SetWillValue(int i, int value) { m_WillValues[i] = value; }
    int GetWillValue(int i) const { return m_WillValues[i]; }

    void SetSpellEffectType(SpellEffectEnum type) { m_SpellEffectType = type; }
    SpellEffectEnum GetSpellEffectType() const { return m_SpellEffectType; }

    void SetSpellEffectValue(int i, int value) { m_SpellEffectValues[i] = value; }
    int GetSpellEffectValue(int i) const { return m_SpellEffectValues[i]; }

    void SetCastTime(int time) { m_OriginalCastTime = time; }
    int GetCastTime() const { return m_OriginalCastTime; }

    void SetChannelEffectType(ChannelEffectEnum type) { m_ChannelEffectType = type; }
    ChannelEffectEnum GetChannelEffectType() const { return m_ChannelEffectType; }

    void SetChannelTime(int time) { m_ChannelTime = time; }
    int GetChannelTime() const { return m_ChannelTime; }

    void SetSpellTarget(SpellTargetEnum target) { m_SpellTarget = target; }
    SpellTargetEnum GetSpellTarget() const { return m_SpellTarget; }

    void SetResolveEffectFlag(int flag) { m_SpellResolveEffect.SetResolveFlags(flag); }
    SpellResolveEffect GetResolvesEffects() const { return m_SpellResolveEffect; }

    friend std::ostream& operator<<(std::ostream& os, const Spell& dt);
};

