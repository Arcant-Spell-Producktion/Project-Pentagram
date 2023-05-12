#include "MapInfoUI.h"

MapInfoUI::MapInfoUI()
	: UIObject("MapInfoUI")
{
	this->position = { 0.0f, 0.0f, 0.0f };
	this->scale = { 600.0f, 600.0f * (9.0f / 16.0f), 1.0f };
	
	m_InfoBG = new UIObject("InfoBG");
	m_InfoBG->color = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_InfoBG->scale = { this->scale.x, 100.0f, 1.0f };
	m_InfoBG->position = { 0.0f, (this->scale.y / 2.0f) - (m_InfoBG->scale.x / 2.0f), 0.0f };

	m_MapInfoText = new TextObject("MapInfoText");
	m_MapInfoText->position = { -(m_InfoBG->scale.x / 2.0f) + 10.0f, 0.0f, 0.0f };
	m_MapInfoText->text = "Map Description";
	m_MapInfoText->fontSize = 20.0f;
	m_MapInfoText->textAlignment = TextAlignment::LEFT;
	m_MapInfoText->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_MapInfoText->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_MapEnterButton = new Button("MapEnterButton");
	m_MapEnterButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
	m_MapEnterButton->SetSlicingBorderMultiplier(0.25f);
	m_MapEnterButton->SetSlicingType(SlicingType::REPEAT);
	m_MapEnterButton->SetSlicingBorderSize(120.0f);
	m_MapEnterButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
	m_MapEnterButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
	m_MapEnterButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
	m_MapEnterButton->scale = { 250.0f, 90.0f, 1.0f };
	m_MapEnterButton->position = { (m_InfoBG->scale.x / 2.0f) - (m_MapEnterButton->scale.x / 2.0f) - 10.0f, 0.0f, 1.0f };
	m_MapEnterButton->textObject.text = "Enter";

	m_InfoBG->SetChildRenderFront(m_MapInfoText);
	m_InfoBG->SetChildRenderFront(m_MapEnterButton);

	this->SetChildRenderFront(m_InfoBG);
	this->SetActive(false);
}

void MapInfoUI::SetMapInfo(const Element::Type& element)
{
	switch (element)
	{
		case Element::Earth:
			this->position = { 625.0f, -350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Earth/stage_earth_background.png");
			this->SetActive(true);
			break;

		case Element::Fire:	
			this->position = { -625.0f, 350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Fire/stage_fire_background.png");
			this->SetActive(true);
			break;

		case Element::Water:
			this->position = { 625.0f, 350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Water/stage_water_background.png");
			this->SetActive(true);
			break;

		case Element::Wind:
            this->position = { -625.0f, -350.0f, 0.0f };
            this->SetTexture("Sprites/Stage/Wind/stage_wind_background.png");
            this->SetActive(true);
			break;

		case Element::Corrupt:
            this->position = { -350.0f, 350.0f, 0.0f };
            //this->SetTexture("Sprites/Stage/Corrupt/stage_corrupt_background.png");
            this->SetActive(true);
            break;
	}
}