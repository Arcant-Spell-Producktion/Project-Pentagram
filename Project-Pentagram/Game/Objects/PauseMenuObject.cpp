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

	m_MenuUI->ResumeButton = new Button("ResumeButton");
	m_MenuUI->ResumeButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_MenuUI->ResumeButton->SetSlicingBorderMultiplier(0.25f);
	m_MenuUI->ResumeButton->SetSlicingType(SlicingType::REPEAT);
	m_MenuUI->ResumeButton->SetSlicingBorderSize(120.0f);
	m_MenuUI->ResumeButton->position = { 0.0f, 150.0f, 0.0f };
	m_MenuUI->ResumeButton->scale = { 350.0f, 90.0f, 1.0f };
	m_MenuUI->ResumeButton->textObject.text = "Resume";
	m_MenuUI->ResumeButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_MenuUI->ResumeButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_MenuUI->ResumeButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	m_MenuUI->ResumeButton->onClick.AddListener([this](Button* button) { this->GetCurrentGameScene()->SetTimeScale(1.0f); SetActive(false); });
	m_MenuUI->SetChildRenderFront(m_MenuUI->ResumeButton);

	m_MenuUI->OptionButton = new Button("OptionButton");
	m_MenuUI->OptionButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_MenuUI->OptionButton->SetSlicingBorderMultiplier(0.25f);
	m_MenuUI->OptionButton->SetSlicingType(SlicingType::REPEAT);
	m_MenuUI->OptionButton->SetSlicingBorderSize(120.0f);
	m_MenuUI->OptionButton->position = { 0.0f, 50.0f, 0.0f };
	m_MenuUI->OptionButton->scale = { 350.0f, 90.0f, 1.0f };
	m_MenuUI->OptionButton->textObject.text = "Options";
	m_MenuUI->OptionButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_MenuUI->OptionButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_MenuUI->OptionButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	m_MenuUI->OptionButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(false); 
			m_OptionMenuObject->SetActive(true); 
		});
	m_MenuUI->SetChildRenderFront(m_MenuUI->OptionButton);

	m_MenuUI->ExitToMenuButton = new Button("ExitMenuButton");
	m_MenuUI->ExitToMenuButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_MenuUI->ExitToMenuButton->SetSlicingBorderMultiplier(0.25f);
	m_MenuUI->ExitToMenuButton->SetSlicingType(SlicingType::REPEAT);
	m_MenuUI->ExitToMenuButton->SetSlicingBorderSize(120.0f);
	m_MenuUI->ExitToMenuButton->position = { 0.0f, -50.0f, 0.0f };
	m_MenuUI->ExitToMenuButton->scale = { 350.0f, 90.0f, 1.0f };
	m_MenuUI->ExitToMenuButton->textObject.text = "Exit To Menu";
	m_MenuUI->ExitToMenuButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_MenuUI->ExitToMenuButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_MenuUI->ExitToMenuButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	//m_MenuUI->ExitToMenuButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_MENU_SCENE); });
	m_MenuUI->ExitToMenuButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(false); 
			m_ConfirmUI->SetActive(true);
			m_ConfirmUI->ConfirmText->text = "Do you want to exit to menu?";
			m_ConfirmUI->Yes->onClick = [this](Button* button) { SceneManager::LoadScene(GameState::GS_MENU_SCENE); };
		});
	m_MenuUI->SetChildRenderFront(m_MenuUI->ExitToMenuButton);

	m_MenuUI->ExitGameButton = new Button("ExitGameButton");
	m_MenuUI->ExitGameButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_MenuUI->ExitGameButton->SetSlicingBorderMultiplier(0.25f);
	m_MenuUI->ExitGameButton->SetSlicingType(SlicingType::REPEAT);
	m_MenuUI->ExitGameButton->SetSlicingBorderSize(120.0f);
	m_MenuUI->ExitGameButton->position = { 0.0f, -150.0f, 0.0f };
	m_MenuUI->ExitGameButton->scale = { 350.0f, 90.0f, 1.0f };
	m_MenuUI->ExitGameButton->textObject.text = "Exit Game";
	m_MenuUI->ExitGameButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_MenuUI->ExitGameButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_MenuUI->ExitGameButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	//m_MenuUI->ExitGameButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_QUIT); });
	m_MenuUI->ExitGameButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(false); 
			m_ConfirmUI->SetActive(true);
			m_ConfirmUI->ConfirmText->text = "Do you want to exit game?";
			m_ConfirmUI->Yes->onClick = [this](Button* button) { SceneManager::LoadScene(GameState::GS_QUIT); };
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
	m_ConfirmUI->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	m_ConfirmUI->scale = { 750.0f, 350.0f, 1.0f };
	m_ConfirmUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_ConfirmUI->SetBlockRaycast(true);
	m_ConfirmUI->SetIsSlicing(true);
	m_ConfirmUI->SetSlicingType(SlicingType::REPEAT);
	m_ConfirmUI->SetSlicingBorderSize(180.0f);
	m_ConfirmUI->SetSlicingBorderMultiplier(0.5f);
	SetChildRenderBack(m_ConfirmUI);

	m_ConfirmUI->ConfirmText = new TextObject("ConfirmationText");
	m_ConfirmUI->ConfirmText->position = { 0.0f, 100.0f, 0.0f };
	m_ConfirmUI->ConfirmText->text = "Are you sure?";
	m_ConfirmUI->ConfirmText->fontSize = 40.0f;
	m_ConfirmUI->ConfirmText->textAlignment = TextAlignment::MID;
	m_ConfirmUI->ConfirmText->color = AC_WHITE;
	m_ConfirmUI->ConfirmText->outlineColor = AC_BLACK;
	m_ConfirmUI->SetChildRenderFront(m_ConfirmUI->ConfirmText);

	m_ConfirmUI->Yes = new Button("Yes_Button");
	m_ConfirmUI->Yes->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_ConfirmUI->Yes->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_ConfirmUI->Yes->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_ConfirmUI->Yes->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	m_ConfirmUI->Yes->SetSlicingBorderMultiplier(0.25f);
	m_ConfirmUI->Yes->SetSlicingType(SlicingType::REPEAT);
	m_ConfirmUI->Yes->SetSlicingBorderSize(120.0f);
	m_ConfirmUI->Yes->scale = { 200.0f, 100.0f, 0.0f };
	m_ConfirmUI->Yes->position = { -150.0f, -50.0f, 0.0f };
	m_ConfirmUI->Yes->textObject.text = "Yes";
	m_ConfirmUI->Yes->textObject.color = AC_WHITE;
	m_ConfirmUI->Yes->textObject.outlineColor = AC_BLACK;
	m_ConfirmUI->SetChildRenderFront(m_ConfirmUI->Yes);

	m_ConfirmUI->No = new Button("No_Button");
	m_ConfirmUI->No->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_ConfirmUI->No->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_ConfirmUI->No->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_ConfirmUI->No->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	m_ConfirmUI->No->onClick.AddListener([this](Button* button)
		{
			m_MenuUI->SetActive(true);
			m_ConfirmUI->SetActive(false);
		});
	m_ConfirmUI->No->SetSlicingBorderMultiplier(0.25f);
	m_ConfirmUI->No->SetSlicingType(SlicingType::REPEAT);
	m_ConfirmUI->No->SetSlicingBorderSize(120.0f);
	m_ConfirmUI->No->scale = { 200.0f, 100.0f, 0.0f };
	m_ConfirmUI->No->position = { 150.0f, -50.0f, 0.0f };
	m_ConfirmUI->No->textObject.text = "No";
	m_ConfirmUI->No->textObject.color = AC_WHITE;
	m_ConfirmUI->No->textObject.outlineColor = AC_BLACK;
	m_ConfirmUI->SetChildRenderFront(m_ConfirmUI->No);

	m_ConfirmUI->CloseButton = new Button("Close_Button");
	m_ConfirmUI->CloseButton->position = { 750.0f / 2.0f, 350.0f / 2.0f, 0.0f };
	m_ConfirmUI->CloseButton->scale = { 50.0f, 50.0f, 1.0f };
	m_ConfirmUI->CloseButton->textObject.text = "X";
	m_ConfirmUI->CloseButton->onClick.AddListener([this](Button* button) 
		{ 
			m_MenuUI->SetActive(true); 
			m_ConfirmUI->SetActive(false); 
		});
	m_ConfirmUI->SetChildRenderFront(m_ConfirmUI->CloseButton);
}