#include "ConfirmUI.h"

ConfirmUI::ConfirmUI(const glm::vec3 &scale)
	: UIObject("ConfirmUI")
{
	this->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	this->scale = scale;
	this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	this->SetBlockRaycast(true);
	this->SetIsSlicing(true);
	this->SetSlicingType(SlicingType::REPEAT);
	this->SetSlicingBorderSize(180.0f);
	this->SetSlicingBorderMultiplier(0.5f);

	m_Background = new UIObject("ConfirmUI_Background");
	m_Background->scale = { 1920.0f, 1080.0f, 1.0f };
	m_Background->color = { 0.0f, 0.0f, 0.0f, 0.7f };
	SetChildRenderBack(m_Background);

	m_ConfirmText = new TextObject("ConfirmationText");
	m_ConfirmText->position = { 0.0f, 80.0f, 0.0f };
	m_ConfirmText->text = "Are you sure?";
	m_ConfirmText->fontSize = 40.0f;
	m_ConfirmText->textAlignment = TextAlignment::MID;
	m_ConfirmText->color = AC_WHITE;
	m_ConfirmText->outlineColor = AC_BLACK;
	SetChildRenderFront(m_ConfirmText);

	m_Yes = new StaticButton("Yes", { 200.0f, 100.0f, 1.0f });
	m_Yes->position = { -150.0f, -50.0f, 0.0f };
	m_Yes->textObject.color = AC_WHITE;
	m_Yes->textObject.outlineColor = AC_BLACK;
	SetChildRenderFront(m_Yes);

	m_No = new StaticButton("No", { 200.0f, 100.0f, 1.0f });
	m_No->onClick.AddListener([this](Button* button)
		{
			this->SetActive(false);
		});
	m_No->position = { 150.0f, -50.0f, 0.0f };
	m_No->textObject.color = AC_WHITE;
	m_No->textObject.outlineColor = AC_BLACK;
	SetChildRenderFront(m_No);

	m_CloseButton = new StaticButton("X", { 75.0f, 75.0f, 1.0f });
	m_CloseButton->SetSlicingBorderMultiplier(0.2f);
	m_CloseButton->position = { (this->scale.x / 2.0f) - (m_CloseButton->scale.x / 2.0f), (this->scale.y / 2.0f) - (m_CloseButton->scale.y / 2.0f), 0.0f };
	m_CloseButton->textObject.fontSize = 44.0f;
	m_CloseButton->onClick.AddListener([this](Button* button)
		{
			this->SetActive(false);
		});
	SetChildRenderFront(m_CloseButton);
}

TextObject* ConfirmUI::GetConfirmText() const { return m_ConfirmText; }
Button* ConfirmUI::GetYesButton() const { return  m_Yes; }
Button* ConfirmUI::GetNoButton() const { return m_No; }
Button* ConfirmUI::GetCloseButton() const { return m_CloseButton; }