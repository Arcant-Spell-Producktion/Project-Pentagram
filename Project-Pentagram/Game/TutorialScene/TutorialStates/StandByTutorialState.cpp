#pragma once
#include "Engine/SceneManager.h"

#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "StandByTutorialState.h"

#include "Game/BattleScene/BattleManager.h"

void StandByTutorialState::OnBattleStateIn()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    TutorialNode* currentNode = RuntimeGameData::GetInstance()->Tutorial.GetTutorialNode();
    battleManager->Data.Pentagram->SetActive(false);

    battleManager->Data.GetCaster(CasterPosition::CasterA)->SpinManaWheel(currentNode->PlayerManaWheel);
    battleManager->Data.GetCaster(CasterPosition::CasterB)->SpinManaWheel();

    Timer = MaxTime;
}

void StandByTutorialState::OnBattleStateUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();

    if (battleManager->Data.IsAllCasterIdle() && Timer > 0)
    {
        Timer -= dt;
        if (Timer < 0.0f)
        {
            BattleManager::GetInstance()->SetBattleState(BattleState::ExplainState);
        }
    }
}

void StandByTutorialState::OnBattleStateOut()
{
    Timer = 0.0f;
    BattleManager* battleManager = BattleManager::GetInstance();
    for (auto caster : battleManager->Data.Casters)
    {
        caster->GetCasterUI()->SetWheelActive(false);
    }
}