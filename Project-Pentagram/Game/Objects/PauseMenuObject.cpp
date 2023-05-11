#include "PauseMenuObject.h"

PauseMenuObject::PauseMenuObject() : UIObject("PauseMenuObject")
{
	this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	canvas = new UIObject("Black_Canvas");
	canvas->scale = { 1920.0f, 1080.0f, 1.0f };
	canvas->color = { 0.0f, 0.0f, 0.0f, 0.5f };
	canvas->SetBlockRaycast(true);
	SetChildRenderBack(canvas);

	bgMenu = new UIObject("BackgroundMenu");
	bgMenu->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	bgMenu->scale = { 500.0f, 550.0f, 1.0f };
	bgMenu->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	bgMenu->SetBlockRaycast(true);
	bgMenu->SetIsSlicing(true);
	bgMenu->SetSlicingType(SlicingType::REPEAT);
	bgMenu->SetSlicingBorderSize(180.0f);
	bgMenu->SetSlicingBorderMultiplier(0.5f);
	SetChildRenderBack(bgMenu);

	resumeButton = new Button("ResumeButton");
	resumeButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	resumeButton->SetSlicingBorderMultiplier(0.25f);
	resumeButton->SetSlicingType(SlicingType::REPEAT);
	resumeButton->SetSlicingBorderSize(120.0f);
	resumeButton->position = { 0.0f, 150.0f, 0.0f };
	resumeButton->scale = { 350.0f, 90.0f, 1.0f };
	resumeButton->textObject.text = "Resume";
	resumeButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	resumeButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	resumeButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	resumeButton->onClick.AddListener([this](Button* button) { this->GetCurrentGameScene()->SetTimeScale(1.0f); SetActive(false); });
	SetChildRenderFront(resumeButton);

	optionButton = new Button("OptionButton");
	optionButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	optionButton->SetSlicingBorderMultiplier(0.25f);
	optionButton->SetSlicingType(SlicingType::REPEAT);
	optionButton->SetSlicingBorderSize(120.0f);
	optionButton->position = { 0.0f, 50.0f, 0.0f };
	optionButton->scale = { 350.0f, 90.0f, 1.0f };
	optionButton->textObject.text = "Options";
	optionButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	optionButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	optionButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	optionButton->onClick.AddListener([this](Button* button) { optionMenuObject->SetActive(true); });
	SetChildRenderFront(optionButton);

	exitToMenuButton = new Button("ExitMenuButton");
	exitToMenuButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	exitToMenuButton->SetSlicingBorderMultiplier(0.25f);
	exitToMenuButton->SetSlicingType(SlicingType::REPEAT);
	exitToMenuButton->SetSlicingBorderSize(120.0f);
	exitToMenuButton->position = { 0.0f, -50.0f, 0.0f };
	exitToMenuButton->scale = { 350.0f, 90.0f, 1.0f };
	exitToMenuButton->textObject.text = "Exit To Menu";
	exitToMenuButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	exitToMenuButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	exitToMenuButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	exitToMenuButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_MENU_SCENE); });
	SetChildRenderFront(exitToMenuButton);

	exitGameButton = new Button("ExitGameButton");
	exitGameButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	exitGameButton->SetSlicingBorderMultiplier(0.25f);
	exitGameButton->SetSlicingType(SlicingType::REPEAT);
	exitGameButton->SetSlicingBorderSize(120.0f);
	exitGameButton->position = { 0.0f, -150.0f, 0.0f };
	exitGameButton->scale = { 350.0f, 90.0f, 1.0f };
	exitGameButton->textObject.text = "Exit Game";
	exitGameButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	exitGameButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	exitGameButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	exitGameButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_QUIT); });
	SetChildRenderFront(exitGameButton);

	optionMenuObject = new OptionMenuObject();
	optionMenuObject->SetActive(false);
	SetChildRenderFront(optionMenuObject);
}

void PauseMenuObject::SetActive(const bool& active)
{
	GameObject::SetActive(active);
	optionMenuObject->SetActive(false);
}
void PauseMenuObject::SetCurrentGameScene(GameScene* gameScene)
{
	currentGameScene = gameScene;
}

GameScene* PauseMenuObject::GetCurrentGameScene() const
{
	return currentGameScene;
}