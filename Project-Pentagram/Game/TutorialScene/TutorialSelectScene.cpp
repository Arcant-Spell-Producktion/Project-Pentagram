#include "TutorialSelectScene.h"
#include "Engine/GameStateController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/StageObject.h"

void TutorialSelectScene::FadeUpdate(const float& dt)
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

void TutorialSelectScene::OnSelect(Element::Type element)
{

}

void TutorialSelectScene::OnConfirm()
{
  
}

void TutorialSelectScene::GameSceneLoad()
{
	std::cout << "Character Scene : Load Completed\n";
}

void TutorialSelectScene::GameSceneInit()
{
    float spacing = 200.0f;

    for (int i = static_cast<int>(TutorialType::WillTutorial); i <= static_cast<int>(TutorialType::CounterTutorial); i++)
    {
        std::stringstream ss;
        ss << "Tur_" << i;

		Button* selectButton = CreateObject(new ScrollButton(TutorialData::GetTutorialName(static_cast<TutorialType>(i)), { 310.0f, 200.0f, 1.0f }, {330.0f, 200.0f, 1.0f}));
		int newLineCount = std::count(selectButton->textObject.text.begin(), selectButton->textObject.text.end(), '\n');
		selectButton->textObject.position.y = (newLineCount * 25.0f);
		selectButton->textObject.fontSize = (newLineCount == 2 ? 34.0f : 36.0f);

        float pos_x = spacing * 2 * (i%4 - 1) - spacing;
        float pos_y = i < 4 ? 150.0f : -150.0f;

        selectButton->position = { pos_x, pos_y, 0.0f };

        selectButton->onClick += [this, i](Button* button)
        {
            RuntimeGameData::GetInstance()->Tutorial.SelectedTutorial = (static_cast<TutorialType>(i));
            FadeOut(2.0f, GameState::GS_TUTORIAL_SCENE);
        };

    }

	TextObject* title = CreateTextObject("Tutorial Selection");
	title->text = "Tutorial Selection";
	title->textAlignment = TextAlignment::MID;
	title->fontSize = 68.0f;
	title->position.y = 400.0f;

	Button* backButton = CreateObject(new ScrollButton("BACK", { 225.0f, 140.0f, 1.0f }, { 250.0f, 140.0f, 1.0f }));
	backButton->textObject.fontSize = 36.0f;
	backButton->position = { -775.0f, -425.0f, 0.0f };
	backButton->onClick.AddListener([this](Button* button)
		{
			SceneManager::LoadScene(GameState::GS_MENU_SCENE);
		});

	// Set FadeScreen Component
	m_FadeScreen = CreateUIObject("fadeScreen");
	m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
    m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_FadeScreen->SetActive(false);

	std::cout << "Character Scene : Initialize Completed\n";
}

void TutorialSelectScene::GameSceneUpdate(float dt)
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

void TutorialSelectScene::GameSceneFree()
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