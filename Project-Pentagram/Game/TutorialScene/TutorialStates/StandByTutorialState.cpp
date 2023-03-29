#pragma once
#include "Engine/SceneManager.h"

#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "StandByTutorialState.h"

#include "Game/TutorialScene/TutorialManager.h"

void StandByTutorialState::OnBattleStateIn()
{
    TutorialManager* battleManager = TutorialManager::GetInstance();
    battleManager->Data.Pentagram->SetActive(false);

    battleManager->Data.StandbyAllCaster();

    Timer = MaxTime;
}

void StandByTutorialState::OnBattleStateUpdate(float dt)
{
    TutorialManager* battleManager = TutorialManager::GetInstance();

    if (battleManager->Data.IsAllCasterIdle() && Timer > 0)
    {
        Timer -= dt;
        if (Timer < 0.0f)
        {
            TutorialManager::GetInstance()->SetBattleState(TutorialState::CastState);
        }
    }
}

void StandByTutorialState::OnBattleStateOut()
{
    Timer = 0.0f;
    TutorialManager* battleManager = TutorialManager::GetInstance();
    battleManager->Data.Pentagram->SetActive(true);
    for (auto caster : battleManager->Data.Casters)
    {
        caster->GetCasterUI()->SetWheelActive(false);
    }
}
