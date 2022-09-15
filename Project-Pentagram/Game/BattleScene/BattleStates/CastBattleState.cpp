#include "CastBattleState.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h""

void PlayerCastUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager->GetData()->GetCurrentCaster();
    SpellCaster* currentCaster = currentController->GetSpellCaster();

    if (currentCaster == nullptr) currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });

    int spellCost = currentCaster->GetSpellCost();
    int canCostSpell = currentCaster->GetMana() - spellCost;

    battleManager->GetData()->pentragramController->SetInvokeButtonActive(canCostSpell >= 0);

    if (Input::IsKeyBeginPressed(GLFW_KEY_4) || currentCaster->GetMana() == 0)//End Turn
    {
        currentController->EndTurn(true);
        battleManager->SwapCaster();
    }
}

void CastBattleState::OnBattleStateIn()
{
}

void CastBattleState::OnBattleStateUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();
    CasterController* currentController = battleManager->GetData()->GetCurrentCaster();//Using currentCaster to display appropriate SpellCircle

    if (currentController->GetSpellCaster()->GetMana() <= 0)
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
            std::cout << " ***************************\n\tCheck value : " << (int)currentController->GetState() << "\n\n";
            SpellCaster* currentCaster = currentController->GetSpellCaster();

            currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });
            battleManager->GetData()->Timeline.AddSpellToTimeline(currentController->CastSpell());

            currentCaster->SetPentagramData({ 1, 1, 1, 1, 3 });
            battleManager->GetData()->Timeline.AddSpellToTimeline(currentController->CastSpell());


            currentController->EndTurn(true);
            battleManager->SwapCaster();
        }
    }
    else
    {
        battleManager->SwapCaster();
    }
}

void CastBattleState::OnBattleStateOut()
{
}
