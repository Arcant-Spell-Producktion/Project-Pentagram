#include "Engine/Scene/MenuScene.h"
#include "Engine/GameStateController.h"
#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/OptionMenuObject.h"
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
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    bool haveActiveSave = gameData.HaveSaveData();

	// Added Stage Background
	objectsList.push_back(new StageObject(static_cast<Element::Type>(rand() % 4)));
	
	// Game Name
	TextObject* gameName = CreateTextObject("gameName");
	gameName->position = { 0.0f, 400.0f, 0.0f };
	gameName->text = "Will O' Witch";
	gameName->textAlignment = TextAlignment::MID;
	gameName->fontSize = 128.0f;
	gameName->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	gameName->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };


    // Play Button
    Button* playButton = CreateObject(new ScrollButton("Play", { 330.0f, 160.0f, 1.0f }, { 350.0f, 160.0f, 1.0f }));

    playButton->position = { 0.0f, 200.0f, 0.0f };

    if (haveActiveSave)
    {
        playButton->position = { 200.0f, 200.0f, 0.0f };
    }
    playButton->onClick.AddListener([this](Button* button) { FadeOut(2.0f, GameState::GS_CHARACTER_SCENE); });

    // Continue Button
    if (haveActiveSave) {
        Button* continueButton = CreateObject(new ScrollButton("Continue", { 330.0f, 160.0f, 1.0f }, { 350.0f, 160.0f, 1.0f }));
        continueButton->position = { -200.0f, 200.0f, 0.0f };
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
	Button* turButton = CreateObject(new ScrollButton("Tutorial", { 330.0f, 160.0f, 1.0f }, { 350.0f, 160.0f, 1.0f }));
    turButton->position = { 0.0f, 0.0f, 0.0f };
    turButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_TUTORIAL_SELECT_SCENE); });

	// Options Button
	Button* optionsButton = CreateObject(new ScrollButton("Options", { 330.0f, 160.0f, 1.0f }, { 350.0f, 160.0f, 1.0f }));
	optionsButton->position = { 0.0f, -200.0f, 0.0f };

	// Exit Button
	Button* exitButton = CreateObject(new ScrollButton("Exit", { 330.0f, 160.0f, 1.0f }, { 350.0f, 160.0f, 1.0f }));
	exitButton->position = { 0.0f, -400.0f, 0.0f };
	exitButton->onClick.AddListener([this](Button* button) { FadeOut(1.0f, GameState::GS_QUIT); });

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
	
	OptionMenuObject* optionMenuObject = CreateObject(new OptionMenuObject());
	optionMenuObject->SetActive(false);

	optionsButton->onClick.AddListener([this, optionMenuObject](Button* button) { optionMenuObject->SetActive(optionMenuObject->IsActive() ? false : true); });
}

void MenuScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	FadeUpdate(dt);

	if (Input::IsKeyPressed(GLFW_KEY_1))
	{
		SceneManager::LoadScene(GameState::GS_DEMO_SCENE);
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_9))
	{
		SceneManager::LoadScene(GameState::GS_BATTLE_SCENE);
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