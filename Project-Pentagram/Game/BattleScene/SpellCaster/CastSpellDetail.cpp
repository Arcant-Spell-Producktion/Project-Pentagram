#include "CastSpellDetail.h"

#include "Game/BattleScene/BattleManager.h"

void CastSpellDetail::OnCast(int* ChannelCount)
{
    ChannelEffectEnum spellChannelType = OriginalSpell->GetChannelEffectType();
    BattleManager* battleManager = BattleManager::GetInstance();
    int cc = 0;
    switch (spellChannelType)
    {
    case ChannelEffectEnum::None:
        this->doCast = true;
        break;
    case ChannelEffectEnum::Wait:
        if (!this->doCast && this->Channel == CastSpellDetail::Head)
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
        if (!this->doCast && this->Channel == CastSpellDetail::Head)
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

    if (ChannelCount != nullptr)
    {
        *ChannelCount = cc;
    }
}
