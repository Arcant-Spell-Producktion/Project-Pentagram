#include "CastSpellDetail.h"

#include "Game/BattleScene/BattleManager.h"

void CastSpellDetail::OnCast(int* ChannelCount)
{
    ChannelEffectEnum spellChannelType = OriginalSpell->GetChannelEffectType();
    BattleManager* battleManager = BattleManager::GetInstance();
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
                newSpell->SelectedTime += newSpell->OriginalSpell->GetChannelTime();
                newSpell->doCast = true;
                newSpell->Channel = CastSpellDetail::End;
                battleManager->Data.Timeline.AddSpellToTimeline(newSpell);
                cc = 1;
                break;
            }
        case ChannelEffectEnum::Active:
        case ChannelEffectEnum::Trap:
        case ChannelEffectEnum::Counter:
            if (!this->doCast)
            {
                cc = 1;
                int endTime = this->SelectedTime + cc;
                for (int i = this->SelectedTime + 1; i <= endTime; i++)
                {
                    CastSpellDetail* newSpell = new CastSpellDetail(*this);
                    newSpell->SelectedTime = i;
                    newSpell->doCast = this->OriginalSpell->GetChannelEffectType() == ChannelEffectEnum::Active;
                    newSpell->ParentSpell = this;
                    newSpell->Channel = i < endTime ? CastSpellDetail::Body : CastSpellDetail::End;
                    battleManager->Data.Timeline.AddSpellToTimeline(newSpell);
                }
            }
            break;
        }
    }

    this->isCasted = true;

    if (ChannelCount != nullptr)
    {
        *ChannelCount = cc;
    }
}

void CastSpellDetail::OnResolve()
{
    BattleManager* battleManager = BattleManager::GetInstance();

    SpellResolveEffect resolveEffect = this->OriginalSpell->GetResolvesEffects();
    CasterPosition casterPosition = this->SpellOwner;
    CasterPosition targetPosition = this->GetTarget();

    CasterController* caster = battleManager->Data.GetCaster(casterPosition);
    CasterController* target = battleManager->Data.GetCaster(targetPosition);

    if (this->TriggeredSpell != nullptr)
    {
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
            this->TriggeredSpell->isCasted = false;
            battleManager->Data.Timeline.GetTimetrack(this->TriggeredSpell->SelectedTime)->RemoveSpell(this->TriggeredSpell);
            this->TriggeredSpell->SelectedTime += 1;
            battleManager->Data.Timeline.AddSpellToTimeline(this->TriggeredSpell);

        }

        for (int i = this->SelectedTime + 1; i <= 10; ++i)
        {
            if (!battleManager->Data.Timeline.GetTimetrack(i)->RemoveChildSpell(this->ParentSpell))
            {
                break;
            }
        }
    }

    if (resolveEffect.DoCancelDamage())
    {
        caster->SetImmune(this->Channel != CastSpellDetail::End);
    }

    if (resolveEffect.DoDamage())
    {
        //Damage Calculation
        int damage = this->GetDamage();
        target->GetEffectManager()->ResolveEffect(EffectResolveType::OnDamageCalculation, 1, &damage);
        if (!target->TakeDamage(damage)) return;
    }

    

    auto effectType = this->OriginalSpell->GetSpellEffectType();
    auto effectValue = this->GetEffectValue();

    if (SpellEffectType::IsEffectTargetEnemy(effectType))
    {
        target->GetEffectManager()->AppliedEffect(effectType, effectValue);
    }
    else
    {
        caster->GetEffectManager()->AppliedEffect(effectType, effectValue);
    }
}
