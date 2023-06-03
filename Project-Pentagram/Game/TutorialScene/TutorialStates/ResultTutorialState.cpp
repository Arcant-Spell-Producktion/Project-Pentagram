#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultTutorialState.h"

void ResultTutorialState::OnBattleStateIn()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    TutorialNode* currentNode = gameData.Tutorial.GetTutorialNode();
    PlayerController* player = dynamic_cast<PlayerController*>(battleManager.Data.GetCaster(CasterPosition::CasterA));

    TutorialGoal goal = currentNode->GetTutorialGoal();
    bool isPlayerAlive = player->IsAlive();
    bool isEnemyAlive = battleManager.Data.GetCaster(CasterPosition::CasterB)->IsAlive();

    bool isSurvied = (goal == TutorialGoal::Survive) && isPlayerAlive;
    bool isKill = (goal == TutorialGoal::Kill) && !isEnemyAlive;
    bool isTutorialComplete = isSurvied || isKill;

    if (!isPlayerAlive)
    {
        player->GetCasterObject()->PlayDiedAnim();
    }

    battleManager.Data.Pentagram->SetActive(false);
    battleManager.Data.Texts->SetActive(true);
    battleManager.Data.Texts->textObject.text = isTutorialComplete ? currentNode->CompleteText : currentNode->RetryText;

    battleManager.Data.Texts->onClick = [this, isTutorialComplete, currentNode](Button* button)
    {
        if (!isTutorialComplete)
        {
            SceneManager::LoadScene(GameState::GS_RESTART);
            return;
        }

        SceneManager::LoadScene(GameState::GS_TUTORIAL_SELECT_SCENE);
    };

}

void ResultTutorialState::OnBattleStateUpdate(float dt)
{
 
}

void ResultTutorialState::OnBattleStateOut()
{

}
