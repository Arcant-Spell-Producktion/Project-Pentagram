#pragma once
#include <vector>
#include "SetupBattleState.h"
#include "CastBattleState.h"
#include "ResolveBattleState.h"
#include "ResultBattleState.h"

class BattleStateModel
{
public:
     static std::vector<BaseBattleState*> GetBattleStates()
     {
         std::vector<BaseBattleState*> states =
         {
             new SetupBattleState(),
             new CastBattleState(),
             new ResolveBattleState(),
             new ResultBattleState()
         };

         return states;
     }
};