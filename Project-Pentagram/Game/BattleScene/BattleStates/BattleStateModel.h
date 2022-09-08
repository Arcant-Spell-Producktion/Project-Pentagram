#pragma once
#include <vector>
#include "BaseBattleState.h"
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
             new CastBattleState()
         };

         return states;
     }
};