#pragma once
#include <vector>
#include "SetupTestState.h"
#include "StandByTestState.h"
#include "CastTestState.h"
#include "ResolveTestState.h"
class TestStateModel
{
public:
     static std::vector<BaseBattleState*> GetTestStates()
     {
         std::vector<BaseBattleState*> states =
         {
             new SetupTestState(),
             new StandByTestState(), 
             new CastTestState(),
             new ResolveTestState(),
         };

         for (BaseBattleState* state : states)
         {
             std::cout << "\t\t !!!!! STATE TO ADD " << static_cast<int>(state->StateID) << std::endl;
         }

         return states;
     }
};