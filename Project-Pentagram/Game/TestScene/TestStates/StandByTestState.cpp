#pragma once
#include "Engine/SceneManager.h"

#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "StandByTestState.h"

#include "Game/BattleScene/BattleManager.h"

void StandByTestState::OnBattleStateIn()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    for (auto caster : battleManager.Data.Casters)
    {
        caster->SetState(CasterState::Idle);
        caster->UpdateCasterUI();
        caster->GetCasterUI()->SetWheelActive(false);
    }

    CasterController* playerC = battleManager.Data.GetCaster(CasterPosition::CasterA);
    playerC->SetHp(999);
    playerC->SetMana(20);

    CasterController* enemy = battleManager.Data.GetCaster(CasterPosition::CasterB);
    enemy->SetHp(999);
    enemy->SetMana(1);

    BattleManager::GetInstance().SetBattleState(BattleState::CastState);
}

void StandByTestState::OnBattleStateUpdate(float dt)
{

}

void StandByTestState::OnBattleStateOut()
{
    Timer = 0.0f;
}
