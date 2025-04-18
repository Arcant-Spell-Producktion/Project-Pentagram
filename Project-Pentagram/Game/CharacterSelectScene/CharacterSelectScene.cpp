#include "CharacterSelectScene.h"
#include "CharacterSelectUI.h"
#include "Engine/GameStateController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/Objects/CursorManager.h"
#include "Game/Objects/StageObject.h"

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
    CursorManager::GetInstance().ChangeParticleElement((int)m_SelectedElement);

    for (int i = 0; i < 4 ; i++)
    {
        CharacterSelectUI* c = dynamic_cast<CharacterSelectUI*>(m_Characters[i]);
        if (i == (int)element)
        {
            c->Select();
			m_CharacterInfoUI->UpdateSelectedCharacter(element);
        }
        else
        {
            c->Deselect();
        }
    }

}

void CharacterSelectScene::OnTest()
{
    dynamic_cast<CharacterSelectUI*>(m_Characters[(int)m_SelectedElement])->Confirm();

    RuntimeGameData& gameData = RuntimeGameData::GetInstance();

    gameData.SetPlayer(
        new PlayerData({ CasterStatDatabase::GetInstance().GetStat(
            m_SelectedElement,CasterType::Player,0), m_SelectedElement, CasterPosition::CasterA }, 0));

    FadeOut(2.0f, GameState::GS_TEST_SCENE);
}

void CharacterSelectScene::OnConfirm()
{
	for (int i = (int)(Element::Earth); i <= (int)(Element::Wind); i++)
	{
		CharacterSelectUI* c = dynamic_cast<CharacterSelectUI*>(m_Characters[i]);
		if (i != (int)m_SelectedElement)
		{
			c->ChangeForm();
		}
	}
    dynamic_cast<CharacterSelectUI*>(m_Characters[(int)m_SelectedElement])->Confirm();

    RuntimeGameData& gameData = RuntimeGameData::GetInstance();

    gameData.SetPlayer(
        new PlayerData({ CasterStatDatabase::GetInstance().GetStat(
            m_SelectedElement,CasterType::Player,0), m_SelectedElement, CasterPosition::CasterA }, 0));

    gameData.Map = new MapData(m_SelectedElement);

    FadeOut(2.0f, GameState::GS_INTRO_SCENE);
}

void CharacterSelectScene::GameSceneLoad()
{
	std::cout << "Character Scene : Load Completed\n";
}

void CharacterSelectScene::GameSceneInit()
{
    float spacing = 200.0f;

    for (int i = (int)(Element::Earth); i <= (int)(Element::Wind); i++)
    {
        Element::Type e = (Element::Type)i;
        CharacterSelectUI* temp = CreateObject(new CharacterSelectUI(e));
        temp->position = { spacing * 2 * (i - 1) - spacing, 150.0f, 0.0f };
        m_Characters.push_back(temp);

        temp->OnCharacterSelect.AddListener([this](Element::Type element) { if(element != m_SelectedElement) { OnSelect(element); } });
    }

	m_CharacterInfoUI = CreateObject(new CharacterInfoUI());
	m_CharacterInfoUI->position = { -400.0f, -300.0f, 0.0f };

	OnSelect(Element::Fire);

	// Select Button
	Button* selectButton = CreateObject(new ScrollButton("Select this Witch", { 650.0f, 160.0f, 1.0f }, { 670.0f, 160.0f, 1.0f }));
	selectButton->position = { 450.0f, -200.0f, 0.0f };
	selectButton->onClick.AddListener([this](Button* button)
        {
            OnConfirm();
        });
	// Test Button
	Button* testButton = CreateObject(new ScrollButton("Test this Witch", { 650.0f, 160.0f, 1.0f }, { 670.0f, 160.0f, 1.0f }));
	testButton->position = { 450.0f, -400.0f, 0.0f };
    testButton->onClick.AddListener([this](Button* button)
        {
            OnTest();
		});

	TextObject* title = CreateTextObject("ChooseYourWitch");
	title->position.y = 475.0f;
	title->text = "Choose Your Witch";
	title->textAlignment = TextAlignment::MID;
	title->fontSize = 92.0f;
	title->color = AC_WHITE;

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

	// Update GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		GameObject*& curObj = objectsList[idx];

		curObj->OnUpdate(dt);
		if (curObj->IsAnimationObject())
		{
			curObj->UpdateAnimation(dt);
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
