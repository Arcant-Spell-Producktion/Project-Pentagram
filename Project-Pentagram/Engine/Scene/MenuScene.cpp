﻿#include "Engine/Scene/MenuScene.h"
#include "Engine/GameStateController.h"
#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/StaticButton.h"
#include <Game/Objects/StageObject.h>

#include "Game/GameData/RuntimeGameData.h"
#include "Game/Objects/CursorManager.h"

void MenuScene::FadeUpdate(const float& dt)
{
	if (m_IsFadeOut)
	{
		m_FadeScreen->color.a = m_FadeCurrentTime / m_FadeTime;
		m_FadeCurrentTime += dt;
		if (m_FadeCurrentTime >= m_FadeTime)
		{
			SceneManager::LoadScene(m_NextState);
		}
	}
}

void MenuScene::GameSceneLoad()
{
    CursorManager::GetInstance().ChangeParticleElement(4);
	std::cout << "Menu Scene : Load Completed\n";
}

void MenuScene::GameSceneInit()
{
	const std::string backgroundPath[] =
	{
		"Sprites/Stage/Earth/stage_earth_background.png",
		"Sprites/Stage/Fire/stage_fire_background.png",
		"Sprites/Stage/Water/stage_water_background.png",
		"Sprites/Stage/Wind/stage_wind_background.png",
		"Sprites/Stage/Corrupt/stage_corrupt_background.png"
	};

    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    bool haveActiveSave = gameData.HaveSaveData();

	// Added Stage Background
	UIObject* background = CreateUIObject("Background");
	background->scale = { WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f };
	background->SetTexture(backgroundPath[rand() % 4]);


	#pragma region Logo
		// Game Logo
		UIObject* gameLogo = CreateUIObject("GameLogo");
		gameLogo->SetTexture("Sprites/Logo/logo_game.png");
		gameLogo->scale = { 400.0f, 300.0f, 1.0f };
		gameLogo->position = { 0.0f, 350.0f, 0.0f };

		// KMUTT Logo
		UIObject* KMUTTLogo = CreateUIObject("KMUTTLogo");
		KMUTTLogo->SetTexture("Sprites/Logo/logo_kmutt.png");
		KMUTTLogo->scale = { 200.0f, 200.0f, 1.0f };
		KMUTTLogo->position = { -850.0f, -410.0f, 0.0f };

		// DDCT Logo
		UIObject* DDCTLogo = CreateUIObject("DDCTLogo");
		DDCTLogo->SetTexture("Sprites/Logo/logo_ddct.png");
		DDCTLogo->scale = { 300.0f, 113.0f, 1.0f };
		DDCTLogo->position = { -600.0f, -460.0f, 0.0f };
	#pragma endregion Logo

	#pragma region Button

		// Play Button
		Button* playButton = CreateObject(new StaticButton("New Game", { 330.0f, 160.0f, 1.0f }));
		playButton->SetSlicingBorderMultiplier(0.5f);
		playButton->position = { 0.0f, 60.0f, 0.0f };

		// Continue Button
		if (haveActiveSave) {
			Button* continueButton = CreateObject(new StaticButton("Continue", { 330.0f, 160.0f, 1.0f }));
			continueButton->SetSlicingBorderMultiplier(0.5f);
			continueButton->position = { -190.0f, 60.0f, 0.0f };
			continueButton->onClick.AddListener([this](Button* button)
				{
					RuntimeGameData& gameData = RuntimeGameData::GetInstance();
					gameData.LoadGameData();

					GameState nextState = GameState::GS_CHARACTER_SCENE;

					CursorManager::GetInstance().ChangeParticleElement(gameData.Player->Element());

					nextState = gameData.Map->IsAtMap ?
						GameState::GS_MAP_SCENE :
						GameState::GS_BATTLE_SCENE;

					FadeOut(2.0f, nextState);

				});
		}

	
		// Tutorial Button
		Button* turButton = CreateObject(new StaticButton("Tutorial", { 330.0f, 160.0f, 1.0f }));
		turButton->SetSlicingBorderMultiplier(0.5f);
		turButton->position = { 190.0f, -140.0f, 0.0f };
		turButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_TUTORIAL_SELECT_SCENE); });

		// Options Button
		Button* optionsButton = CreateObject(new StaticButton("Options", { 330.0f, 160.0f, 1.0f }));
		optionsButton->SetSlicingBorderMultiplier(0.5f);
		optionsButton->position = { -190.0f, -140.0f, 0.0f };

		// Exit Button
		Button* exitButton = CreateObject(new StaticButton("Exit", { 330.0f, 160.0f, 1.0f }));
		exitButton->SetSlicingBorderMultiplier(0.5f);
		exitButton->position = { 0.0f, -340.0f, 0.0f };
		exitButton->onClick.AddListener([this](Button* button) { FadeOut(1.0f, GameState::GS_QUIT); });

		// Credit Button
		Button* creditButton = CreateObject(new StaticButton("Credit", { 330.0f, 160.0f, 1.0f }));
		creditButton->SetSlicingBorderMultiplier(0.5f);
		creditButton->position = { 770.0f, -410.0f, 0.0f };
		creditButton->onClick.AddListener([this](Button* button)
			{
                SceneManager::LoadScene(GameState::GS_CREDIT_SCENE);
			});

		// Option Menu
		optionMenuObject = CreateObject(new OptionMenuObject());
		optionMenuObject->SetActive(false);

		optionsButton->onClick.AddListener([this](Button* button) { optionMenuObject->SetActive(optionMenuObject->IsActive() ? false : true); });


		// ConfirmUI for PlayButton
		confirmUI = CreateObject(new ConfirmUI({ 900.0f, 350.0f, 1.0f }));
		confirmUI->GetConfirmText()->fontSize = 32.0f;
		confirmUI->GetConfirmText()->text =
	R"(Are you sure you want to start a new game?
	All your saved files will be deleted.)";
		confirmUI->SetActive(false);
		if (haveActiveSave)
		{
			playButton->position = { 190.0f, 60.0f, 0.0f };
			playButton->onClick.AddListener([this](Button* button)
				{
					confirmUI->SetActive(true);
					confirmUI->GetYesButton()->onClick = [this](Button* button) { FadeOut(2.0f, GameState::GS_CHARACTER_SCENE); };
				});
		}
		else
		{
			playButton->onClick.AddListener([this](Button* button) { FadeOut(2.0f, GameState::GS_CHARACTER_SCENE); });
		}

	#pragma endregion Button

	// Set FadeScreen Component
	m_FadeScreen = CreateUIObject("fadeScreen");
	m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
	m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_FadeScreen->SetActive(false);

	BGMController* bgm = audioController.CreateBGM({ "Audio/BGM/Water/bgm_water_1-1.wav", "Audio/BGM/Water/bgm_water_1-3.wav","Audio/BGM/Water/bgm_water_1-4.wav" },
		{ 1.0f, 1.0f, 1.0f, 1.0f });

	/*
	Usage of BGMController
		(*bgm)[2]->SetVolume(0.5f);
	*/

	bgm->Play();

	std::cout << "Menu Scene : Initialize Completed\n";
}

void MenuScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	FadeUpdate(dt);

	if (Input::IsKeyPressed(GLFW_KEY_1))
	{
		SceneManager::LoadScene(GameState::GS_DEMO_SCENE);
	}
    else if (Input::IsKeyPressed(GLFW_KEY_2))
    {
        SceneManager::LoadScene(GameState::GS_INTRO_SCENE);
    }
	else if (Input::IsKeyBeginPressed(GLFW_KEY_9))
	{
		SceneManager::LoadScene(GameState::GS_BATTLE_SCENE);
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
	{
		if (confirmUI->IsActive()) { confirmUI->SetActive(false); }
		else if (optionMenuObject->IsActive()) { optionMenuObject->SetActive(false); }
	}

	// Update GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		GameObject*& curObj = objectsList[idx];

		curObj->OnUpdate(dt);
		if (curObj->IsAnimationObject())
		{
			curObj->UpdateAnimation(dt);
		}
		if (curObj->GetTag() == GameObjectTag::PARTICLE && Input::IsKeyBeginPressed(GLFW_KEY_4))
		{
			curObj->SetActive(curObj->IsActive() ? false : true);
		}
	}
	// Update UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		UIObject*& curObj = uiObjectsList[idx];

		if (!curObj->IsActive()) { continue; }
		curObj->OnUpdate(dt);
	}
}

void MenuScene::GameSceneFree()
{
	// Free GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		delete objectsList[idx];
	}
	// Free UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		delete uiObjectsList[idx];
	}
	//soundSystem->FreeSound();
	std::cout << "Menu Scene : Free Memory Completed\n";
}