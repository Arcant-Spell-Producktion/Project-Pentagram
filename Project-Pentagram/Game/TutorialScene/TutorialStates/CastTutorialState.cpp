#include "CastTutorialState.h"

#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/EnemyController.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"

void CastTutorialState::EnemyCastUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager->Data.GetCurrentCaster();

    currentController->EndTurn(true);
    battleManager->SwapCaster();
}

void CastTutorialState::PlayerCastUpdate(float dt)
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

void CastTutorialState::OnBattleStateIn()
{
}

void CastTutorialState::OnBattleStateUpdate(float dt)
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

void CastTutorialState::OnBattleStateOut()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    battleManager->Data.Pentagram->SetActive(false);
    battleManager->Data.Timeline.UI->UpdatePreviewIcon(0);
}
