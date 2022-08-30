#pragma once
#include "Game/Spells/Spell.h"

enum class Caster
{
    NONE,
    CasterA,
    CasterB,
};

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

