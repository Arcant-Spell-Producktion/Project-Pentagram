#pragma once
#include "Game/GameData/CasterData/CasterPosition.h"
#include "Game/Spells/Spell.h"

class CastSpellDetail
{
    public:
        CasterPosition SpellOwner;
        Spell* OriginalSpell;
        int SelectedWill;
        int SelectedEffect;
        int SelectedTime;
        bool isCasted = false;

        CastSpellDetail(CasterPosition position,Spell* spell, int will, int effect, int time) :
            SpellOwner(position),
            OriginalSpell(spell),
            SelectedWill(will),
            SelectedEffect(effect),
            SelectedTime(time)
        {}

        friend ostream& operator<<(ostream& os, const CastSpellDetail& detail)
        {
            os << "\n\tSpell: " << detail.OriginalSpell->GetSpellName() <<" By: "<<(int)detail.SpellOwner << "\n";

            os << "\tWill: " << detail.SelectedWill << "\n";

            os << "\tDamage:  " << detail.OriginalSpell->GetWillValue(detail.SelectedWill -1) << " \n";

            os << "\tEffect Type: " << SideEffectType::GetString(detail.OriginalSpell->GetSideEffectType()) << "\n";
           
            os << "\tEffect: " << detail.SelectedEffect << "\n";

            os << "\tEffect V:  " << detail.OriginalSpell->GetSideEffectValue(detail.SelectedEffect -1) << " \n";

            os << "\tCast Time: " << detail.SelectedTime << "(" << detail.OriginalSpell->GetCastTime() << ")" << "\n";

            os << "\tChannel Type: " << ChannelEffectType::GetString(detail.OriginalSpell->GetChannelEffectType()) << "\n";

            os << "\tChannel Time: " << detail.OriginalSpell->GetChannelTime() << "\n";

            return os;
        };
};

