#pragma once
#include "Spell.h"

using namespace std;

const string SideEffectType::enum_string[] = {
    "None",
    "Mark",
    "Burn"
};

const string ChannelEffectType::enum_string[] = {
    "None",
    "Wait",
    "Active"
};

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

    os << "Effect Type: " << SideEffectType::GetString(spell.m_SideEffectType) << "\n";

    os << "Effect:[ ";
    for (int i = 0; i < 6; i++)
    {
        os << spell.m_SideEffectValues[i];
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
