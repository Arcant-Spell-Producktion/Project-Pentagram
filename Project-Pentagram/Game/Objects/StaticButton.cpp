#include "StaticButton.h"

StaticButton::StaticButton(std::string text, const glm::vec3& scale)
	: Button("Static_Button")
{
	this->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	this->SetSlicingBorderMultiplier(0.25f);
	this->SetSlicingType(SlicingType::REPEAT);
	this->SetSlicingBorderSize(120.0f);
	this->scale = scale;
	this->textObject.text = text;
	this->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	this->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	this->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
}