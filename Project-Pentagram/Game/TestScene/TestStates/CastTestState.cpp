#include "CastTestState.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/EnemyController.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"

void CastTestState::EnemyCastUpdate(float dt)
{
    BattleManager& battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager.Data.GetCurrentCaster();
    CasterManager* currentCaster = currentController->GetCasterManager();

    dynamic_cast<EnemyController*>(currentController)->CastEnemySpell();

    currentController->EndTurn();
    battleManager.SwapCaster();
}

void CastTestState::PlayerCastUpdate(float dt)
{
    BattleManager& battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager.Data.GetCurrentCaster();
    CasterManager* currentCaster = currentController->GetCasterManager();

    if (currentCaster == nullptr) currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });

    //battleManager.Data.Pentagram->SetCastButtonActive(currentCaster->CanCastSpell());

    if (Input::IsKeyBeginPressed(GLFW_KEY_4) || currentCaster->GetMana() == 0)//End Turn
    {
        currentController->EndTurn(true);
        battleManager.SwapCaster();
    }
}

void CastTestState::OnBattleStateIn()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    battleManager.Data.StartRound();

    if (battleManager.Data.GetCurrentCaster()->IsAlive())
    {
    battleManager.Data.GetCurrentCaster()->StartTurn(); //TODO:: Need to add check if caster is alive before start turn

    battleManager.Data.Pentagram->SetActive(true);
    battleManager.Data.Pentagram->SetPentagramOwner(battleManager.Data.GetCurrentCaster());
    }
}

void CastTestState::OnBattleStateUpdate(float dt)
{
    BattleManager& battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager.Data.GetCurrentCaster();//Using currentCaster to display appropriate SpellCircle

    if (currentController->GetCasterManager()->GetMana() <= 0)
    {
        std::cout << "FORCED PASS\n";
        currentController->EndTurn(true);
        battleManager.SwapCaster();
        return;
    }

    if (currentController->GetState() != CasterState::Passed)
    {
        if (dynamic_cast<PlayerController*>(currentController) != nullptr)
        {
            PlayerCastUpdate(dt);
        }
        else
        {
            EnemyCastUpdate(dt);
        }
    }
    else
    {
        battleManager.SwapCaster();
    }
}

void CastTestState::OnBattleStateOut()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    battleManager.Data.Pentagram->SetActive(false);
    battleManager.Data.Timeline.UI->UpdatePreviewIcon(0);

    battleManager.Data.EndCastPhase();
}
