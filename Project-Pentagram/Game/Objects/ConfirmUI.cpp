#include "ConfirmUI.h"

ConfirmUI::ConfirmUI()
	: UIObject("ConfirmUI")
{
	this->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	this->scale = { 750.0f, 350.0f, 1.0f };
	this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	this->SetBlockRaycast(true);
	this->SetIsSlicing(true);
	this->SetSlicingType(SlicingType::REPEAT);
	this->SetSlicingBorderSize(180.0f);
	this->SetSlicingBorderMultiplier(0.5f);

	ConfirmText = new TextObject("ConfirmationText");
	ConfirmText->position = { 0.0f, 100.0f, 0.0f };
	ConfirmText->text = "Are you sure?";
	ConfirmText->fontSize = 40.0f;
	ConfirmText->textAlignment = TextAlignment::MID;
	ConfirmText->color = AC_WHITE;
	ConfirmText->outlineColor = AC_BLACK;
	SetChildRenderFront(ConfirmText);

	Yes = new Button("Yes_Button");
	Yes->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	Yes->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	Yes->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	Yes->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	Yes->SetSlicingBorderMultiplier(0.25f);
	Yes->SetSlicingType(SlicingType::REPEAT);
	Yes->SetSlicingBorderSize(120.0f);
	Yes->scale = { 200.0f, 100.0f, 0.0f };
	Yes->position = { -150.0f, -50.0f, 0.0f };
	Yes->textObject.text = "Yes";
	Yes->textObject.color = AC_WHITE;
	Yes->textObject.outlineColor = AC_BLACK;
	SetChildRenderFront(Yes);

	No = new Button("No_Button");
	No->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	No->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	No->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	No->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	No->onClick.AddListener([this](Button* button)
		{
			this->SetActive(false);
		});
	No->SetSlicingBorderMultiplier(0.25f);
	No->SetSlicingType(SlicingType::REPEAT);
	No->SetSlicingBorderSize(120.0f);
	No->scale = { 200.0f, 100.0f, 0.0f };
	No->position = { 150.0f, -50.0f, 0.0f };
	No->textObject.text = "No";
	No->textObject.color = AC_WHITE;
	No->textObject.outlineColor = AC_BLACK;
	SetChildRenderFront(No);

	CloseButton = new Button("Close_Button");
	CloseButton->position = { 750.0f / 2.0f, 350.0f / 2.0f, 0.0f };
	CloseButton->scale = { 50.0f, 50.0f, 1.0f };
	CloseButton->textObject.text = "X";
	CloseButton->onClick.AddListener([this](Button* button)
		{
			this->SetActive(false);
		});
	SetChildRenderFront(CloseButton);
}

TextObject* ConfirmUI::GetConfirmText() const { return ConfirmText; }
Button* ConfirmUI::GetYesButton() const { return  Yes; }
Button* ConfirmUI::GetNoButton() const { return No; }
Button* ConfirmUI::GetCloseButton() const { return CloseButton; }