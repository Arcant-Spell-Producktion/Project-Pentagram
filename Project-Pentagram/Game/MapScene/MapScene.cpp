#include "MapScene.h"
#include "Engine/GameStateController.h"
#include "Game/GameData/RuntimeGameData.h"
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

    for (int i = 0; i < 4; i++)
    {
        Element::Type e = static_cast<Element::Type>(i);
        MapNode* node = CreateObject(new MapNode(e));
        node->SetActive(gameData->Map->CanVisitChapter(e));

        node->onClick.AddListener([this, e, gameData](Button* button)
            {
                gameData->Map->SelectChapter(e);
        FadeOut(2.0f, GameState::GS_BATTLE_SCENE);
            });

        switch (e)
        {
        case Element::Earth:
            node->position = { 300.0f, -100.0f, 0.0f };
            node->onClick.RemoveAllListeners();//TODO REMOVE AFTER IMPLEMENT
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

	if (Input::IsKeyPressed(GLFW_KEY_1))
	{
		SceneManager::LoadScene(GameState::GS_DEMO_SCENE);
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