#include "ResolveBattleState.h"
#include <Game/BattleScene/BattleManager.h>

void ResolveBattleState::OnBattleStateIn()
{
}

void ResolveBattleState::OnBattleStateUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();

    for (int i = 0; i < 10; i++)
    {
        std::cout << "Resovel Track: " << i << "\n";

        SpellTimetrack* track = battleManager->GetData()->Timeline.GetTimetrack(i);
        std::cout << "\tGet Track: " << i << "\n";
        std::cout << "\tTrack Size: " << track->GetSpellList().size() << "\n";
       /* for (auto csd : track->GetSpellList())
        {
            std::cout << *csd << "\n";
        }*/

        CasterPosition casterPosition = track->GetWillCompareResult();
        CasterPosition targetPosition = casterPosition == CasterPosition::CasterB ? CasterPosition::CasterA : CasterPosition::CasterB;
        std::cout << "\tGet casterToResolve: " << (int)casterPosition << "\n";
        //use casterToResolve play WillCompare Animation

        track->UpdateTimetrack();

        if (casterPosition >= CasterPosition::CasterA)
        {
            for (CastSpellDetail* spell : track->GetSpellList())
            {
                if (spell->isCasted) continue;

                spell->isCasted = true;

                switch (spell->OriginalSpell->GetChannelEffectType())
                {
                case ChannelEffectType::None:
                    spell->doCast = true;
                    break;
                case ChannelEffectType::Wait:
                    if (!spell->doCast)
                    {
                    CastSpellDetail* newSpell = new CastSpellDetail(*spell);
                    newSpell->SelectedTime += newSpell->OriginalSpell->GetChannelTime();
                    newSpell->doCast = true;
                    battleManager->GetData()->Timeline.AddSpellToTimeline(newSpell,true);
                    break;
                    }
                case ChannelEffectType::Active:
                    if (!spell->doCast)
                    {
                        for (int i = spell->SelectedTime +1; i <= spell->SelectedTime + spell->OriginalSpell->GetChannelTime(); i++)
                        {
                        CastSpellDetail* newSpell = new CastSpellDetail(*spell);
                        newSpell->SelectedTime = i;
                        newSpell->doCast = true;
                        battleManager->GetData()->Timeline.AddSpellToTimeline(newSpell, true);
                        }
                    }
                    break;
                }
                
                if (spell->doCast)
                {
                    CasterController* caster = battleManager->GetData()->GetCaster(casterPosition);
                    CasterController* target = battleManager->GetData()->GetCaster(targetPosition);

                    //Damage Calculation
                    target->TakeDamage(spell->GetDamage());

                    //TODO: resolve the spell effect
                }

                //TODO: check battle end condition
            }
        }
        else
        {
            std::cout << "\n\tTIED OR NONE\n\n";
            continue;
        }
    }
    

    //if(battle end)
    //{}
    //else
    battleManager->SetBattleState(BattleState::CastState);
    //battleManager->SwapCaster();
}

void ResolveBattleState::OnBattleStateOut()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    battleManager->GetData()->Timeline.UpdateTimeline();
}
