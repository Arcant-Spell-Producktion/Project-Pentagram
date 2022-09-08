#pragma once
#include <vector>
#include "SetupBattleState.h"
#include "CastBattleState.h"
#include "ResolveBattleState.h"

class BattleStateModel
{
public:
     static std::vector<BaseBattleState*> GetBattleStates()
     {
         std::vector<BaseBattleState*> states =
         {
             new SetupBattleState(),
             new CastBattleState(),
             new ResolveBattleState()
         };

         return states;
     }
};