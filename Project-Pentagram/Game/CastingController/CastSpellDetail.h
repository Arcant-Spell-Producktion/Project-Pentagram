#pragma once
#include "../Spells/Spell.h"
class CastSpellDetail
{
    public:
        Caster SpellOwner;
        Spell* OriginalSpell;
        int SelectedWill;
        int SelectedEffect;
        int SelectedTime;

        CastSpellDetail(Caster caster,Spell* spell, int will, int effect, int time) :
            SpellOwner(caster),
            OriginalSpell(spell),
            SelectedWill(will),
            SelectedEffect(effect),
            SelectedTime(time)
        {}
};

enum Caster
{
    NONE,
    CasterA,
    CasterB,
};
