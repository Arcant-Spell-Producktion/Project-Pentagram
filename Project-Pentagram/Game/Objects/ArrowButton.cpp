#include "ArrowButton.h"

ArrowButton::ArrowButton() : StaticButton("", { 240.0f, 160.0f, 1.0f })
{
	ArrowSprite = new UIObject("BackButton_ArrowSprite");
	ArrowSprite->scale = { 140.0f, 90.0f, 1.0f };
	ArrowSprite->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_scroll_button-arrow.png");
	ArrowSprite->SetSpriteByIndex(1, 0);
	this->SetChildRenderFront(ArrowSprite);
}