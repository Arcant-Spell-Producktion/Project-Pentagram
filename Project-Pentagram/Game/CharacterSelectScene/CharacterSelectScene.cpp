#include "CharacterSelectScene.h"
#include "Engine/GameStateController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "CharacterSelectUI.h"
#include <Game/Objects/StageObject.h>

void CharacterSelectScene::FadeUpdate(const float& dt)
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

void CharacterSelectScene::OnSelect(Element::Type element)
{
    m_SelectedElement = element;

    for (int i = 0; i < 2 ; i++)
    {
        CharacterSelectUI* c = dynamic_cast<CharacterSelectUI*>(m_Characters[i]);
        if (i+1 == (int)element)//TODO:: remove +1 after add EARTH
        {
            c->Select();
        }
        else
        {
            c->Deselect();
        }
    }

}

void CharacterSelectScene::OnConfirm()
{
    FadeOut(2.0f, GameState::GS_BATTLE_SCENE);
    dynamic_cast<CharacterSelectUI*>(m_Characters[(int)m_SelectedElement - 1])->Confirm();//TODO:: remove -1 after add EARTH
    RuntimeGameData::GetInstance()->Player = 
        new PlayerData({ CasterStatDatabase::GetInstance()->GetStat(
            m_SelectedElement,CasterType::Player,0), m_SelectedElement, CasterPosition::CasterA }, 0);

}

void CharacterSelectScene::GameSceneLoad()
{
	std::cout << "Character Scene : Load Completed\n";
}

void CharacterSelectScene::GameSceneInit()
{
    float spacing = 175.0f;

    for (int i = (int)(Element::Fire); i <= (int)(Element::Water); i++)
    {
        Element::Type e = (Element::Type)i;
        CharacterSelectUI* temp = CreateObject(new CharacterSelectUI(e));
        temp->position = { spacing * 2 * (i - 1) - spacing, 0.0f, 0.0f };
        m_Characters.push_back(temp);

        temp->OnCharacterSelect.AddListener([this](Element::Type element) { if(element != m_SelectedElement) { OnSelect(element); } });
    }

    OnSelect(Element::Fire);

	// Select Button
	Button* selectButton = CreateObject(new ScrollButton("Select"));
	selectButton->position = { 0.0f, -400.0f, 0.0f };
	selectButton->onClick.AddListener([this](Button* button)
        {
            OnConfirm();
        });

	// Set FadeScreen Component
	m_FadeScreen = CreateUIObject("fadeScreen");
	m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
    m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_FadeScreen->SetActive(false);

	std::cout << "Character Scene : Initialize Completed\n";
}

void CharacterSelectScene::GameSceneUpdate(float dt)
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

void CharacterSelectScene::GameSceneFree()
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
	std::cout << "Character Scene : Free Memory Completed\n";
}