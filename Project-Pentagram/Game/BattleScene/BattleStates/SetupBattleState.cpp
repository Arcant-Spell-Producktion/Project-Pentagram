#pragma once
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"


#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"

#include "Engine/Audio/AudioController.h"

#include "SetupBattleState.h"

#include "Game/BattleScene/SpellCaster/BossController.h"

void SetupBattleState::OnBattleStateIn()
{
    BattleManager& bm = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    NodeData* currentNode = gameData.Map->GetNextNode();
    std::cout << "DEBUG ENEMY ELEMENT: " << (int)currentNode->GetEnemyData().Element() << "\n";

    bm.Data.AddCaster(new PlayerController(*(RuntimeGameData::GetInstance().Player)));

    if (currentNode->GetEnemyData().EnemyType() == CasterType::BigBoss)
    {
        EnemyData bossData = currentNode->GetEnemyData();
        int remainHp = bossData.Stat().MaxHealth;

        bossData.Stat().MaxHealth = 800;

        BossController* bc = new BossController(bossData);
        bc->SetHp(remainHp);

        bm.Data.AddCaster(bc);
    }
    else
    {
        bm.Data.AddCaster(new EnemyController( currentNode->GetEnemyData()));
    }

    AudioController& audioController = AudioController::GetInstance();
    BGMController* bgm = nullptr;

    switch(currentNode->GetEnemyData().Element())
    {
    case Element::Earth:
        bgm = audioController.CreateBGM({ "Audio/BGM/Earth/bgm_earth_1-1.wav", "Audio/BGM/Earth/bgm_earth_1-2.wav","Audio/BGM/Earth/bgm_earth_1-3.wav" }, { 1.0f, 1.0f, 1.0f, 1.0f });
        break;
    case Element::Fire:
        bgm = audioController.CreateBGM({ "Audio/BGM/Fire/bgm_fire_1-1.wav", "Audio/BGM/Fire/bgm_fire_1-2.wav","Audio/BGM/Fire/bgm_fire_1-3.wav" }, { 1.0f, 1.0f, 1.0f, 1.0f });
        break;
    case Element::Water:
        bgm = audioController.CreateBGM({ "Audio/BGM/Water/bgm_water_2-1.wav", "Audio/BGM/Water/bgm_water_2-2.wav","Audio/BGM/Water/bgm_water_2-3.wav" }, { 1.0f, 1.0f, 1.0f, 1.0f });
        break;
    case Element::Wind:
        bgm = audioController.CreateBGM({ "Audio/BGM/Wind/bgm_wind_1-1.wav", "Audio/BGM/Wind/bgm_wind_1-2.wav", "Audio/BGM/Wind/bgm_wind_1-3.wav" }, { 1.0f, 1.0f, 1.0f });
        break;
    case Element::Corrupt:
        bgm = audioController.CreateBGM({ "Audio/BGM/FinalBoss/bgm_finalboss_1-1.wav", "Audio/BGM/FinalBoss/bgm_finalboss_1-2.wav", "Audio/BGM/FinalBoss/bgm_finalboss_1-3.wav" }, { 1.0f, 1.0f, 1.0f });
        break;
     default:
         bgm = audioController.CreateBGM({ "Audio/BGM/Water/bgm_water_2-1.wav", "Audio/BGM/Water/bgm_water_2-2.wav","Audio/BGM/Water/bgm_water_2-3.wav" }, { 1.0f, 1.0f, 1.0f, 1.0f });
        break;
    }

    bgm->Play();

    for (auto caster : bm.Data.Casters)
    {
        caster->UpdateCasterUI();
    }
}

void SetupBattleState::OnBattleStateUpdate(float dt)
{
}

void SetupBattleState::OnBattleStateOut()
{
}
