#pragma once
#include "Spell.h"

using namespace std;

ostream& operator<<(ostream& os, const Spell& spell)
{
    os << "Spell: " << spell.m_Name << "\n";

    os << "Will:[ ";
    for (int i = 0; i < 6; i++)
    {
        os << spell.m_WillValues[i];
        if (i < 5)
        {
            os << " , ";
        }
    }
    os << " ]\n";

    os << "Effect Type: " << SpellEffectType::GetString(spell.m_SpellEffectType) << "\n";

    os << "Effect:[ ";
    for (int i = 0; i < 6; i++)
    {
        os << spell.m_SpellEffectValues[i];
        if (i < 5)
        {
            os << " , ";
        }
    }
    os << " ]\n";

    os << "Cast Time: " << spell.m_OriginalCastTime << "\n";

    os << "Channel Type: " << ChannelEffectType::GetString(spell.m_ChannelEffectType) << "\n";

    os << "Channel Time: " << spell.m_ChannelTime << "\n";

    return os;
}
