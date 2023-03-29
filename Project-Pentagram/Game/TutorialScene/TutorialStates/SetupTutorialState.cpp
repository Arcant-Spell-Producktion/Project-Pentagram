#pragma once
#include "Game/TutorialScene/TutorialManager.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"

#include "Engine/Audio/AudioController.h"

#include "SetupTutorialState.h"

#include "Game/BattleScene/SpellCaster/EnemyController.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"

void SetupTutorialState::OnBattleStateIn()
{
    TutorialManager* bm = TutorialManager::GetInstance();
    RuntimeGameData* gameData = RuntimeGameData::GetInstance();
    NodeData* currentNode = gameData->Map->GetNextNode();
    std::cout << "DEBUG ENEMY ELEMENT: " << (int)currentNode->GetEnemyData().Element() << "\n";

    bm->Data.AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));

    bm->Data.AddCaster(new EnemyController( currentNode->GetEnemyData()));

    AudioController* audioController = AudioController::GetInstance();
    BGMController* bgm = nullptr;

    switch(currentNode->GetEnemyData().Element())
    {
    case Element::Earth: break;
    case Element::Fire:
        bgm = audioController->CreateBGM({ "Audio/BGM/Fire/bgm_fire_1-1.wav", "Audio/BGM/Fire/bgm_fire_1-2.wav","Audio/BGM/Fire/bgm_fire_1-3.wav" }, { 1.0f, 1.0f, 1.0f, 1.0f });
        break;
    case Element::Water:
        bgm = audioController->CreateBGM({ "Audio/BGM/Water/bgm_water_2-1.wav", "Audio/BGM/Water/bgm_water_2-2.wav","Audio/BGM/Water/bgm_water_2-3.wav" }, { 1.0f, 1.0f, 1.0f, 1.0f });
        break;
    case Element::Wind:
        break;
  
    }

    bgm->Play();
}

void SetupTutorialState::OnBattleStateUpdate(float dt)
{
}

void SetupTutorialState::OnBattleStateOut()
{
}
