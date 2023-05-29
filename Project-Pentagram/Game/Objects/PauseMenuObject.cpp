#include "PauseMenuObject.h"

PauseMenuObject::PauseMenuObject() : UIObject("PauseMenuObject")
{
	this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	canvas = new UIObject("Black_Canvas");
	canvas->scale = { 1920.0f, 1080.0f, 1.0f };
	canvas->color = { 0.0f, 0.0f, 0.0f, 0.5f };
	canvas->SetBlockRaycast(true);
	SetChildRenderBack(canvas);

	InitMenuUI();
	InitConfirmUI();
}

void PauseMenuObject::ToggleEvent(float& timeScale)
{
	if (m_ConfirmUI->IsActive())
	{
		m_ConfirmUI->SetActive(false);
		m_MenuUI->SetActive(true);
	}
	else if (m_OptionMenuObject->IsActive())
	{
		m_OptionMenuObject->SetActive(false);
		m_MenuUI->SetActive(true);
	}
	else if (this->IsActive())
	{
		this->SetActive(false);
		timeScale = 1.0f;
	}
	else
	{
		this->SetActive(true);
		timeScale = 0.0f;
	}
}

void PauseMenuObject::SetActive(const bool& active)
{
	GameObject::SetActive(active);
	m_MenuUI->SetActive(active);
	m_OptionMenuObject->SetActive(false);
	m_ConfirmUI->SetActive(false);
}
void PauseMenuObject::SetCurrentGameScene(GameScene* gameScene)
{
	currentGameScene = gameScene;
}

GameScene* PauseMenuObject::GetCurrentGameScene() const
{
	return currentGameScene;
}

void PauseMenuObject::InitMenuUI()
{
	m_MenuUI = new MenuUI();
	m_MenuUI->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	m_MenuUI->scale = { 500.0f, 550.0f, 1.0f };
	m_MenuUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_MenuUI->SetBlockRaycast(true);
	m_MenuUI->SetIsSlicing(true);
	m_MenuUI->SetSlicingType(SlicingType::REPEAT);
	m_MenuUI->SetSlicingBorderSize(180.0f);
	m_MenuUI->SetSlicingBorderMultiplier(0.5f);
	SetChildRenderBack(m_MenuUI);

	m_MenuUI->ResumeButton = new StaticButton("Resume");
	m_MenuUI->ResumeButton->position = { 0.0f, 150.0f, 0.0f };
	m_MenuUI->ResumeButton->onClick.AddListener([this](Button* button) { this->GetCurrentGameScene()->SetTimeScale(1.0f); SetActive(false); });
	m_MenuUI->SetChildRenderFront(m_MenuUI->ResumeButton);

	m_MenuUI->OptionButton = new StaticButton("Options");
	m_MenuUI->OptionButton->position = { 0.0f, 50.0f, 0.0f };
	m_MenuUI->OptionButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(false); 
			m_OptionMenuObject->SetActive(true); 
		});
	m_MenuUI->SetChildRenderFront(m_MenuUI->OptionButton);

	m_MenuUI->ExitToMenuButton = new StaticButton("Exit To Menu");
	m_MenuUI->ExitToMenuButton->position = { 0.0f, -50.0f, 0.0f };
	m_MenuUI->ExitToMenuButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(false); 
			m_ConfirmUI->SetActive(true);
			m_ConfirmUI->GetConfirmText()->text = "Do you want to exit to menu?";
			m_ConfirmUI->GetYesButton()->onClick = [this](Button* button) { SceneManager::LoadScene(GameState::GS_MENU_SCENE); };
		});
	m_MenuUI->SetChildRenderFront(m_MenuUI->ExitToMenuButton);

	m_MenuUI->ExitGameButton = new StaticButton("Exit Game");
	m_MenuUI->ExitGameButton->position = { 0.0f, -150.0f, 0.0f };
	m_MenuUI->ExitGameButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(false); 
			m_ConfirmUI->SetActive(true);
			m_ConfirmUI->GetConfirmText()->text = "Do you want to exit game?";
			m_ConfirmUI->GetYesButton()->onClick = [this](Button* button) { SceneManager::LoadScene(GameState::GS_QUIT); };
		});
	m_MenuUI->SetChildRenderFront(m_MenuUI->ExitGameButton);

	m_OptionMenuObject = new OptionMenuObject();
	m_OptionMenuObject->SetActive(false);
	m_OptionMenuObject->GetCloseButton()->onClick.AddListener([this](Button* button)
		{
			m_MenuUI->SetActive(true);
		});
	SetChildRenderFront(m_OptionMenuObject);
}
void PauseMenuObject::InitConfirmUI()
{
	m_ConfirmUI = new ConfirmUI();
	SetChildRenderBack(m_ConfirmUI);

	m_ConfirmUI->GetNoButton()->onClick.AddListener([this](Button* button)
		{
			m_MenuUI->SetActive(true);
		});

	m_ConfirmUI->GetCloseButton()->onClick.AddListener([this](Button* button)
		{ 
			m_MenuUI->SetActive(true);
		});
}