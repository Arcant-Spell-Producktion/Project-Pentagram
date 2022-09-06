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
};

