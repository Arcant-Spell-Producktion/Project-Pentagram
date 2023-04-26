#include "MapScene.h"
#include "Engine/GameStateController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "Game/MapScene/CasterStatUI.h"
#include "Game/MapScene/MapInfoUI.h"
#include "MapNode.h"


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

    RuntimeGameData* gameData = RuntimeGameData::GetInstance();

    auto MapBGObject = CreateGameObject("MapBG");
    MapBGObject->SetTexture("Sprites/Map/map.png");
    MapBGObject->scale = { 1920.0f,1080.0f,0.0f };

	m_Character = CreateGameObject("Character");
	m_Character->scale = { 200.0f, 200.0f, 1.0f };
	m_Character->SetIsAnimationObject(true);
	m_Character->SetIsAnimationLoop(true);
	switch (gameData->Player->Element())
	{
		case Element::Earth:
			m_Character->SetTexture("Sprites/Character/Player/character_player_earth.png");
			m_Character->position = { 300.0f, -100.0f + 10.0f, 0.0f };
			break;
		case Element::Fire:
			m_Character->SetTexture("Sprites/Character/Player/character_player_fire.png");
			m_Character->position = { -250.0f, 130.0f + 10.0f, 0.0f };
			break;
		case Element::Water:
			m_Character->SetTexture("Sprites/Character/Player/character_player_water.png");
			m_Character->position = { 210.0f, 350.0f + 10.0f, 0.0f };
			break;
		case Element::Wind:
			m_Character->SetTexture("Sprites/Character/Player/character_player_wind.png");
			m_Character->position = { -60.0f, -220.0f + 10.0f, 0.0f };
			break;
	}


	MapInfoUI* mapInfoUI = CreateObject(new MapInfoUI());

    for (int i = 0; i < 4; i++)
    {
        Element::Type e = static_cast<Element::Type>(i);
        MapNode* node = CreateObject(new MapNode(e));
        node->SetActive(gameData->Map->CanVisitChapter(e));

        node->onClick.AddListener([this, e, gameData, mapInfoUI](Button* button)
            {
				mapInfoUI->SetMapInfo(e);

				mapInfoUI->m_MapEnterButton->onClick.AddListener([this, e, gameData, button](Button* _button)
					{
						// TEMP
						button->SetActive(false);

						m_MoveCharacter = true;
						m_StartPoint = m_Character->position;
						m_Destination = button->position;
						gameData->Map->SelectChapter(e);
						FadeOut(4.0f, GameState::GS_BATTLE_SCENE);
					});
            });

        switch (e)
        {
			case Element::Earth:
				node->position = { 300.0f, -100.0f, 0.0f };
				break;
			case Element::Fire:
				node->position = { -250.0f, 130.0f, 0.0f };
				break;
			case Element::Water:
				node->position = { 210.0f, 350.0f, 0.0f };
				break;
			case Element::Wind:
				node->position = { -60.0f, -220.0f, 0.0f };
				node->onClick.RemoveAllListeners();//TODO REMOVE AFTER IMPLEMENT
				break;
        }

    }

	CasterStatUI* casterStatUI = CreateObject(new CasterStatUI(gameData->Player));

    // Set FadeScreen Component
    m_FadeScreen = CreateUIObject("fadeScreen");
    m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
    m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_FadeScreen->SetActive(false);
}

void MapScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	FadeUpdate(dt);

	if (m_MoveCharacter)
	{
		m_CurrentMoveTime = (m_CurrentMoveTime + dt > m_MoveTime ? m_MoveTime : m_CurrentMoveTime + dt);
		m_Character->position = m_StartPoint + (m_CurrentMoveTime / m_MoveTime) * (m_Destination - m_StartPoint);
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