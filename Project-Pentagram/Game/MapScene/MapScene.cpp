﻿#include "MapScene.h"
#include "Engine/GameStateController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "Game/MapScene/CasterStatUI.h"
#include "Game/MapScene/MapInfoUI.h"
#include "Game/Objects/PauseMenuObject.h"
#include "MapNode.h"

PauseMenuObject* map_PauseMenuObject;
const std::string MapFogTextures[4] =
{
    "Sprites/Map/map_fog_Earth.png",
    "Sprites/Map/map_fog_Fire.png",
    "Sprites/Map/map_fog_Water.png",
    "Sprites/Map/map_fog_Wind.png"
};

void MapScene::FadeUpdate(const float& dt)
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

void MapScene::GameSceneLoad()
{
	std::cout << "Map Scene : Load Completed\n";
}

void MapScene::GameSceneInit()
{
	std::cout << "Map Scene : Initialize Completed\n";

	const glm::vec3 earthNodePosition = { 523.0f, 0.0f, 0.0f };
	const glm::vec3 fireNodePosition = { -456.0f, 85.0f, 0.0f };
	const glm::vec3 waterNodePosition = { 232.0f, 380.0f, 0.0f };
	const glm::vec3 windNodePosition = { -172.0f, -220.0f, 0.0f };
	const glm::vec3 corruptNodePosition = { 10.0f, 120.0f, 0.0f };

	const glm::vec3 offset = { 0.0f, 10.0f, 0.0f };


    RuntimeGameData& gameData = RuntimeGameData::GetInstance();

    GameObject* MapBGObject = CreateGameObject("MapBG");
    MapBGObject->SetTexture("Sprites/Map/world_map.png");
    MapBGObject->scale = { 1920.0f,1080.0f,0.0f };

    for (int i = 0; i < 4; i++)
    {
        Element::Type element = static_cast<Element::Type>(i);
        if (element != (gameData.Player->Element()) && !gameData.Map->IsChapterComplete(element))
        {
           GameObject* fogObject = CreateGameObject("Fog");
            fogObject->SetTexture(MapFogTextures[i]);
            fogObject->scale = { 1920.0f,1080.0f,0.0f };
            fogObject->color.a = 0.7f;

            MapBGObject->SetChildRenderFront(fogObject);
        }
    }

	m_Character = CreateGameObject("Character");
	m_Character->scale = { 200.0f, 200.0f, 1.0f };
	m_Character->SetIsAnimationObject(true);
	m_Character->SetIsAnimationLoop(true);
	switch (gameData.Player->Element())
	{
		case Element::Earth:
			m_Character->SetTexture("Sprites/Character/Player/character_player_earth.png");
			break;
		case Element::Fire:
			m_Character->SetTexture("Sprites/Character/Player/character_player_fire.png");
			break;
		case Element::Water:
			m_Character->SetTexture("Sprites/Character/Player/character_player_water.png");
			break;
		case Element::Wind:
			m_Character->SetTexture("Sprites/Character/Player/character_player_wind.png");
			break;
	}

    switch (gameData.Map->GetCurrentChapter())
    {
		case Element::Earth:
			m_Character->position = earthNodePosition + offset;
			break;
		case Element::Fire:
			m_Character->position = fireNodePosition + offset;
			break;
		case Element::Water:
			m_Character->position = waterNodePosition + offset;
			break;
		case Element::Wind:
			m_Character->position = windNodePosition + offset;
			break;
    }


	MapInfoUI* mapInfoUI = CreateObject(new MapInfoUI());

    for (int i = 0; i <= 4; i++)
    {
        Element::Type e = static_cast<Element::Type>(i);
        MapNode* node = CreateObject(new MapNode(e));
        node->SetActive(gameData.Map->CanVisitChapter(e));

        node->onClick.AddListener([this, e, &gameData, mapInfoUI](Button* button)
            {
				mapInfoUI->SetMapInfo(e);

				mapInfoUI->m_MapEnterButton->onClick = ([this, e, &gameData, button](Button* _button)
					{
						// TEMP
						button->SetActive(false);

						m_MoveCharacter = true;
						m_StartPoint = m_Character->position;
						m_Destination = button->position;
						gameData.Map->SelectChapter(e);
						FadeOut(4.0f, GameState::GS_BATTLE_SCENE);
					});
            });

        switch (e)
        {
			case Element::Earth:
				node->position = earthNodePosition;
				break;
			case Element::Fire:
				node->position = fireNodePosition;
				break;
			case Element::Water:
				node->position = waterNodePosition;
				break;
			case Element::Wind:
				node->position = windNodePosition;
				break;
            case Element::Corrupt:
                node->position = corruptNodePosition;
                break;
        }

    }

	// Disable CasterStatUI
	// CasterStatUI* casterStatUI = CreateObject(new CasterStatUI(gameData->Player));


    m_LevelUpText = CreateTextObject("Level Up!");
    m_LevelUpText->text = "Level Up!";
    m_LevelUpText->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_Character->SetChildRenderFront(m_LevelUpText);
    m_LevelUpText->SetActive(gameData.Player->Element() != gameData.Map->GetCurrentChapter());
    m_LevelUpText->position.x -= 100.0f;
    m_LevelUpText->position.y += 140.0f;

	map_PauseMenuObject = CreateObject(new PauseMenuObject());
	map_PauseMenuObject->SetCurrentGameScene(this);
	map_PauseMenuObject->SetActive(false);


    // Set FadeScreen Component
    m_FadeScreen = CreateUIObject("fadeScreen");
    m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
    m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_FadeScreen->SetActive(false);

    gameData.Map->IsAtMap = true;
    gameData.SaveGameData();
}

void MapScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	FadeUpdate(dt);

	if (m_MoveCharacter)
	{
        m_LevelUpText->SetActive(false);
		m_CurrentMoveTime = (m_CurrentMoveTime + dt > m_MoveTime ? m_MoveTime : m_CurrentMoveTime + dt);
		m_Character->position = m_StartPoint + (m_CurrentMoveTime / m_MoveTime) * (m_Destination - m_StartPoint);
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
	{
		map_PauseMenuObject->ToggleEvent(timeScale);
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

void MapScene::GameSceneFree()
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
	std::cout << "Map Scene : Free Memory Completed\n";
}