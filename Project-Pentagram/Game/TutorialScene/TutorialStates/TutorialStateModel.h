#pragma once
#include <vector>
#include "SetupTutorialState.h"
#include "StandByTutorialState.h"
#include "CastTutorialState.h"
#include "ResolveTutorialState.h"
#include "ResultTutorialState.h"
class TutorialStateModel
{
public:
     static std::vector<BaseTutorialState*> GetTutorialStates()
     {
         std::vector<BaseTutorialState*> states =
         {
             new SetupTutorialState(),
             new StandByTutorialState(),
             new CastTutorialState(),
             new ResolveTutorialState(),
             new ResultTutorialState()
         };

         return states;
     }
};