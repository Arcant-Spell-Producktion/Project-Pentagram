#pragma once
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/BattleScene/SpellCaster/EnemyController.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"

#include "Engine/Audio/AudioController.h"

#include "SetupTestState.h"

void SetupTestState::OnBattleStateIn()
{
    BattleManager& bm = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    auto player = RuntimeGameData::GetInstance().Player;
    bm.Data.AddCaster(new PlayerController(*(RuntimeGameData::GetInstance().Player)));

    bm.Data.AddCaster(new EnemyController(
        EnemyData(CasterData(
            CasterStat(
                100, 
                { 6,6,6,6,6,6 }
            ),
            player->Element(),
            CasterPosition::CasterB),
            CasterType::Minion,
            CasterMoveSet())));

    CasterController* playerC = bm.Data.GetCaster(CasterPosition::CasterA);
    playerC->SetHp(999);
    playerC->SetMana(20);

    CasterController* enemy = bm.Data.GetCaster(CasterPosition::CasterB);
    enemy->SetHp(999);
    enemy->SetMana(1);
   
    AudioController& audioController = AudioController::GetInstance();
    BGMController* bgm = nullptr;

    switch(player->Element())
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
        bgm = audioController.CreateBGM({ "Audio/BGM/Wind/bgm_wind_sub.wav" }, { 1.0f });
        break;
  
    }

    bgm->Play();
}

void SetupTestState::OnBattleStateUpdate(float dt)
{
}

void SetupTestState::OnBattleStateOut()
{
}
