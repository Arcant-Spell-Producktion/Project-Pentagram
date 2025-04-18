#pragma once
#include <vector>
#include "SetupTutorialState.h"
#include "ExplainTutorialState.h"
#include "StandByTutorialState.h"
#include "CastTutorialState.h"
#include "ResolveTutorialState.h"
#include "ResultTutorialState.h"
class TutorialStateModel
{
public:
     static std::vector<BaseBattleState*> GetTutorialStates()
     {
         std::vector<BaseBattleState*> states =
         {
             new SetupTutorialState(),
             new ExplainTutorialState(),
             new StandByTutorialState(),
             new CastTutorialState(),
             new ResolveTutorialState(),
             new ResultTutorialState()
         };

         for (BaseBattleState* state : states)
         {
             std::cout << "\t\t !!!!! STATE TO ADD " << static_cast<int>(state->StateID) << std::endl;
         }

         return states;
     }
};