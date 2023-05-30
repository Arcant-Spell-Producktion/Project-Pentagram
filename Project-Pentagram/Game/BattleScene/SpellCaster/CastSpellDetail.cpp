#include "CastSpellDetail.h"

#include "Game/BattleScene/BattleManager.h"

void CastSpellDetail::OnCast(int* ChannelCount)
{
    ChannelEffectEnum spellChannelType = OriginalSpell->GetChannelEffectType();
    BattleManager& battleManager = BattleManager::GetInstance();
    int cc = 0;

    if (this->Channel == CastSpellDetail::Head)
    {

        switch (spellChannelType)
        {
        case ChannelEffectEnum::None:
            this->doCast = true;
            break;
        case ChannelEffectEnum::Wait:
            if (!this->doCast)
            {
                CastSpellDetail* newSpell = new CastSpellDetail(*this);
                newSpell->SelectedTime += newSpell->GetSpellDetail()->GetChannelTime();
                newSpell->doCast = true;
                newSpell->Channel = CastSpellDetail::End;
                battleManager.Data.Timeline.AddSpellToTimeline(newSpell);
                cc = 1;
                break;
            }
        case ChannelEffectEnum::Active:
        case ChannelEffectEnum::Trap:
        case ChannelEffectEnum::Counter:
            if (!this->doCast)
            {
                this->doCast = true;

                int startTime = this->SelectedTime;
                int endTime = startTime + this->GetSpellDetail()->GetChannelTime();
                for (int i = startTime + 1; i <= endTime; i++)
                {
                    CastSpellDetail* newSpell = new CastSpellDetail(*this);
                    newSpell->SelectedTime = i;
                    newSpell->doCast = this->GetSpellDetail()->GetChannelEffectType() == ChannelEffectEnum::Active;
                    newSpell->ParentSpell = this;
                    newSpell->Channel = i < endTime ? CastSpellDetail::Body : CastSpellDetail::End;
                    battleManager.Data.Timeline.AddSpellToTimeline(newSpell);

                    std::cout <<"\t add more spell at t -> "<< i << " : " << newSpell->Channel << "\n";
                }
            }
            break;
        }
    }
    else
    {
        if (spellChannelType >= ChannelEffectEnum::Trap && this->TriggeredSpell != nullptr)
        {
            this->doCast = true;
        }
    }

    SpellResolveEffect resolveEffect = this->GetSpellDetail()->GetResolvesEffects();
    CasterController* caster = battleManager.Data.GetCaster(this->SpellOwner);
    if (resolveEffect.DoCancelDamage())
    {
        caster->SetImmune(this->Channel != CastSpellDetail::End);
    }

    this->isCasted = true;

    if (ChannelCount != nullptr)
    {
        *ChannelCount = cc;
    }
}

void CastSpellDetail::OnResolve()
{
    BattleManager& battleManager = BattleManager::GetInstance();

    SpellResolveEffect resolveEffect = this->GetSpellDetail()->GetResolvesEffects();
    CasterPosition casterPosition = this->SpellOwner;
    CasterPosition targetPosition = this->GetTarget();

    CasterController* caster = battleManager.Data.GetCaster(casterPosition);
    CasterController* target = battleManager.Data.GetCaster(targetPosition);

    if (this->GetSpellDetail()->GetChannelEffectType() >= ChannelEffectEnum::Active && this->Channel == CastSpellDetail::End && this->TriggeredSpell == nullptr)
    {
        //Spell End with out trigger
        return;
    }

    if (this->TriggeredSpell != nullptr)
    {

        std::cout << "\t Resolve Triggered SPELL \n";

        this->TriggeredSpell->TriggeredSpell = nullptr;

        if (!resolveEffect.DoCancelSpell())
        {
            this->TriggeredSpell->OnResolve();
        }
        if (resolveEffect.DoReflectDamage())
        {
            //Damage Calculation
            int damage = this->TriggeredSpell->GetDamage();
            target->GetEffectManager()->ResolveEffect(EffectResolveType::OnDamageCalculation, 1, &damage);
            if (!target->TakeDamage(damage)) return;
        }
        if (resolveEffect.DoDelaySpell())
        {
            battleManager.Data.Timeline.GetTimetrack(this->TriggeredSpell->SelectedTime)
                                                       ->RemoveSpell(this->TriggeredSpell);
            battleManager.Data.Timeline.UI->RemoveIconFromTrack(this->TriggeredSpell->SelectedTime, this->TriggeredSpell);

            CastSpellDetail* newSpell = new CastSpellDetail(*this->TriggeredSpell);

            newSpell->isCasted = false;
            newSpell->SelectedTime += 1;

            if (!battleManager.Data.Timeline.GetTimetrack(newSpell->SelectedTime - 1)->IsTrackFull(newSpell->SpellOwner))
            {
                battleManager.Data.Timeline.AddSpellToTimeline(newSpell);
            }
        }

        for (int i = this->SelectedTime ; i <= 10; ++i)
        {
            CastSpellDetail* toDelete = nullptr;
            toDelete = battleManager.Data.Timeline.GetTimetrack(i)->RemoveChildSpell(this->ParentSpell);
            if (toDelete != nullptr)
            {
                std::cout << "\t remove child spell from track: " << i << "\n";

                battleManager.Data.Timeline.UI->RemoveIconFromTrack(i, toDelete);
                delete toDelete;
            }else
            {
                break;
            }
        }
    }

    if (resolveEffect.DoDamage())
    {
        //Damage Calculation
        int damage = this->GetDamage();
        target->GetEffectManager()->ResolveEffect(EffectResolveType::OnDamageCalculation, 1, &damage);
        if (!target->TakeDamage(damage)) return;
    }

    AppliedEffect();
}

void CastSpellDetail::AppliedEffect(bool isWinCompare)
{
    BattleManager& battleManager = BattleManager::GetInstance();

    SpellResolveEffect resolveEffect = this->GetSpellDetail()->GetResolvesEffects();
    CasterPosition casterPosition = this->SpellOwner;
    CasterPosition targetPosition = this->GetTarget();

    CasterController* caster = battleManager.Data.GetCaster(casterPosition);
    CasterController* target = battleManager.Data.GetCaster(targetPosition);

    auto effectType = this->GetSpellDetail()->GetSpellEffectType();
    auto effectValue = this->GetEffectValue();

    bool isApplyByWillWin = SpellEffectType::IsEffectApplyWillCompareWin(effectType);

    if (isWinCompare != isApplyByWillWin) return;

    if (SpellEffectType::IsEffectTargetEnemy(effectType))
    {
        target->GetEffectManager()->AppliedEffect(effectType, effectValue);
    }
    else
    {
        caster->GetEffectManager()->AppliedEffect(effectType, effectValue);
    }
}
