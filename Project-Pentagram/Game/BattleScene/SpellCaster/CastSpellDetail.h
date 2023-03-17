#pragma once
#include "Game/GameData/CasterData/CasterPosition.h"
#include "Game/Spells/Spell.h"

class CastSpellDetail
{
    public:
        enum ChannelType
        {
            Head,
            Body,
            End
        };

        CasterPosition SpellOwner;
        Spell* OriginalSpell = nullptr;
        int SelectedWill;
        int SelectedEffect;
        int SelectedTime;
        bool isCasted = false;
        bool doCast = false;
        bool isHidden = false;

        ChannelType Channel = ChannelType::Head;

        CastSpellDetail* TriggeredSpell = nullptr;

        CastSpellDetail* ParentSpell = nullptr;

        CasterPosition GetTarget() const
        {
            if (OriginalSpell->GetSpellTarget() == SpellTargetEnum::Opponent)
            {
                return SpellOwner == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;
            }
            else if (OriginalSpell->GetSpellTarget() == SpellTargetEnum::Self)
            {
                return SpellOwner;
            }
        }

        int GetIndex() const { return OriginalSpell->GetSpellIndex(); }
        int GetDamage() const { return OriginalSpell->GetWillValue(SelectedWill - 1); }
        int GetEffectValue() const { return OriginalSpell->GetSpellEffectValue(SelectedEffect - 1); }

        bool DoWillCompare() const
        {
            switch (OriginalSpell->GetChannelEffectType()) {
            case ChannelEffectEnum::None: 
                return true;
            case ChannelEffectEnum::Wait:
                return Channel != ChannelType::Head;
            case ChannelEffectEnum::Active:
            case ChannelEffectEnum::Trap:
            case ChannelEffectEnum::Counter:
                return Channel == ChannelType::Head;
            }
        }

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

        void OnCast(int* ChannelCount = nullptr);

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

