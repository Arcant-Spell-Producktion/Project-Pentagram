#include "CastBattleState.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/EnemyController.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"

void CastBattleState::EnemyCastUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager->Data.GetCurrentCaster();
    CasterManager* currentCaster = currentController->GetCasterManager();

    dynamic_cast<EnemyController*>(currentController)->CastEnemySpell();

    currentController->EndTurn();
    battleManager->SwapCaster();
}

void CastBattleState::PlayerCastUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager->Data.GetCurrentCaster();
    CasterManager* currentCaster = currentController->GetCasterManager();

    if (currentCaster == nullptr) currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });

    int spellCost = currentCaster->GetSpellCost();
    int canCostSpell = currentCaster->GetMana() - spellCost;

    battleManager->Data.Pentagram->SetCastButtonActive(canCostSpell >= 0);

    if (Input::IsKeyBeginPressed(GLFW_KEY_4) || currentCaster->GetMana() == 0)//End Turn
    {
        currentController->EndTurn(true);
        battleManager->SwapCaster();
    }
}

void CastBattleState::OnBattleStateIn()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    battleManager->Data.StartRound();

    if (battleManager->Data.GetCurrentCaster()->IsAlive())
    {
    battleManager->Data.GetCurrentCaster()->StartTurn(); //TODO:: Need to add check if caster is alive before start turn

    battleManager->Data.Pentagram->SetActive(true);
    battleManager->Data.Pentagram->SetPentagramOwner(battleManager->Data.GetCurrentCaster());
    }
}

void CastBattleState::OnBattleStateUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager->Data.GetCurrentCaster();//Using currentCaster to display appropriate SpellCircle

    if (currentController->GetCasterManager()->GetMana() <= 0)
    {
        std::cout << "FORCED PASS\n";
        currentController->EndTurn(true);
        battleManager->SwapCaster();
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
        battleManager->SwapCaster();
    }
}

void CastBattleState::OnBattleStateOut()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    battleManager->Data.Pentagram->SetActive(false);
    battleManager->Data.Timeline.UI->UpdatePreviewIcon(0);

    for (auto caster : battleManager->Data.Casters)
    {
        caster->GetCasterManager()->ResetBuff();
        caster->GetCasterManager()->ResetDebuff();
        caster->GetEffectManager()->OnCastPhaseEnd();
    }
}
