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
        bool doCast = false;

        int GetIndex() const { return OriginalSpell->GetSpellIndex(); }
        int GetDamage() const { return OriginalSpell->GetWillValue(SelectedWill - 1); }
        int GetEffectValue() const { return OriginalSpell->GetSpellEffectValue(SelectedEffect - 1); }

        CastSpellDetail(CasterPosition position,Spell* spell, int will, int effect, int time = 0,bool isCted = false, bool do_cast = false) :
            SpellOwner(position),
            OriginalSpell(spell),
            SelectedWill(will),
            SelectedEffect(effect),
            SelectedTime(time),
            isCasted(isCted),
            doCast(do_cast)
        {
            if (SelectedTime == 0)
            {
                SelectedTime = OriginalSpell->GetCastTime();
            }
        }

        void UpdateDetail(int will, int effect, int time)
        {
            SelectedWill = will;
            SelectedEffect = effect;
            SelectedTime = time;
        }

        friend std::ostream& operator<<(std::ostream& os, const CastSpellDetail& detail)
        {
            os << "\n\tSpell: " << detail.OriginalSpell->GetSpellName() <<" By: "<<(int)detail.SpellOwner << "\n";

            os << "\tWill: " << detail.SelectedWill << "\n";

            os << "\tDamage:  " << detail.GetDamage() << " \n";

            os << "\tEffect Type: " << SpellEffectType::GetString(detail.OriginalSpell->GetSpellEffectType()) << "\n";
           
            os << "\tEffect: " << detail.SelectedEffect << "\n";

            os << "\tEffect V:  " << detail.OriginalSpell->GetSpellEffectValue(detail.SelectedEffect -1) << " \n";

            os << "\tCast Time: " << detail.SelectedTime << "(" << detail.OriginalSpell->GetCastTime() << ")" << "\n";

            os << "\tChannel Type: " << ChannelEffectType::GetString(detail.OriginalSpell->GetChannelEffectType()) << "\n";

            os << "\tChannel Time: " << detail.OriginalSpell->GetChannelTime() << "\n";

            return os;
        };
};

