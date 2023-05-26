#pragma once
#include "Game/BattleScene/BattleManager.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"

#include "Engine/Audio/AudioController.h"

#include "SetupTutorialState.h"

#include "Game/BattleScene/SpellCaster/EnemyController.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"

void SetupTutorialState::OnBattleStateIn()
{
    BattleManager& bm = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    TutorialNode* currentNode = gameData.Tutorial.GetTutorialNode();
    std::cout << "DEBUG ENEMY ELEMENT: " << (int)currentNode->GetEnemyData().Element() << "\n";


    gameData.Player = new PlayerData(*currentNode->GetPlayerData(), 0);
    bm.Data.AddCaster(new PlayerController(*gameData.Player));

    bm.Data.AddCaster(new EnemyController( currentNode->GetEnemyData()));

    CasterController* player = bm.Data.GetCaster(CasterPosition::CasterA);
    player->SetHp(currentNode->PlayerHP);
    player->SetMana(currentNode->PlayerMana);

    CasterController* enemy = bm.Data.GetCaster(CasterPosition::CasterB);
    enemy->SetHp(currentNode->EnemyHP);
    enemy->SetMana(currentNode->EnemyMana);
    for (PentagramData_T spellPentagram : currentNode->TutorialSpells)
    {
        enemy->GetCasterManager()->SetPentagramData(spellPentagram);
        dynamic_cast<EnemyController*>(enemy)->CastEnemySpell(spellPentagram);
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
  
    }

    bgm->Play();

    bm.Data.StartRound();

    if (bm.Data.GetCurrentCaster()->IsAlive())
    {
        bm.Data.GetCurrentCaster()->StartTurn(); //TODO:: Need to add check if caster is alive before start turn

        bm.Data.Pentagram->SetPentagramOwner(bm.Data.GetCurrentCaster());
    }
}

void SetupTutorialState::OnBattleStateUpdate(float dt)
{
}

void SetupTutorialState::OnBattleStateOut()
{
}
