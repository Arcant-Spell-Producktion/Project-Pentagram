#include "Engine/Scene/MenuScene.h"
#include "Engine/GameStateController.h"
#include "Game/Objects/ScrollButton.h"
#include <Game/Objects/StageObject.h>

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
	std::cout << "Menu Scene : Load Completed\n";
}

void MenuScene::GameSceneInit()
{
	// Added Stage Background
	objectsList.push_back(new StageObject(Element::Water));
	
	// Game Name
	TextObject* gameName = CreateTextObject("gameName");
	gameName->position = { 0.0f, 350.0f, 0.0f };
	gameName->text = "Will O' Witch";
	gameName->textAlignment = TextAlignment::MID;
	gameName->fontSize = 128.0f;
	gameName->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	gameName->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	// Play Button
	Button* playButton = CreateObject(new ScrollButton("Play"));
	playButton->position = { 0.0f, 0.0f, 0.0f };
	playButton->onClick.AddListener([this](Button* button) { FadeOut(2.0f, GameState::GS_CHARACTER_SCENE); });

	// Exit Button
	Button* exitButton = CreateObject(new ScrollButton("Exit"));
	exitButton->position = { 0.0f, -200.0f, 0.0f };
	exitButton->onClick.AddListener([this](Button* button) { FadeOut(1.0f, GameState::GS_QUIT); });

	// Set FadeScreen Component
	m_FadeScreen = CreateUIObject("fadeScreen");
	m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
	m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	BGMController* bgm = audioController->CreateBGM({ "Audio/BGM/Water/bgm_water_1-1.wav", "Audio/BGM/Water/bgm_water_1-3.wav","Audio/BGM/Water/bgm_water_1-4.wav" },
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