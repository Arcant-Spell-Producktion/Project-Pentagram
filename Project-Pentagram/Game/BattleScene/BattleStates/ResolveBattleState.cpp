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

       /* for (auto csd : track->GetSpellList())
        {
            std::cout << *csd << "\n";
        }*/

        CasterPosition casterToResolve = track->GetWillCompareResult();
        std::cout << "\tGet casterToResolve: " << (int)casterToResolve << "\n";
        //use casterToResolve play WillCompare Animation

        track->UpdateTimetrack();

        if (casterToResolve >= CasterPosition::CasterA)
        {
            for (CastSpellDetail* spell : track->GetSpellList())
            {
                if (spell->isCasted) continue;

                //TODO: resolve the spell

                spell->isCasted = true;

                //TODO: check battle end condition
            }
        }
        else
        {
            continue;
        }
    }
    battleManager->GetData()->Timeline.UpdateTimeline();

    //if(battle end)
    //{}
    //else
    battleManager->GetData()->StandbyAllCaster();
    battleManager->SetBattleState(BattleState::CastState);
    battleManager->SwapCaster();
}

void ResolveBattleState::OnBattleStateOut()
{
}
