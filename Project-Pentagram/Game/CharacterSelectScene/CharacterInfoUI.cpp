#include "CharacterInfoUI.h"

CharacterInfoUI::CharacterInfoUI()
	: UIObject("CharacterInfoUI")
{
	this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_InfoBackground = new UIObject("CharacterInfoUI_InfoBackground");
	m_InfoBackground->position = { 0.0f, 0.0f, 0.0f };
	m_InfoBackground->scale = { 900.0f, 400.0f, 1.0f };
	m_InfoBackground->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	m_InfoBackground->SetIsSlicing(true);
	m_InfoBackground->SetSlicingType(SlicingType::REPEAT);
	m_InfoBackground->SetSlicingBorderSize(160.0f);
	m_InfoBackground->SetSlicingBorderMultiplier(0.5f);
	this->SetChildRenderFront(m_InfoBackground);

	m_CasterInfo = new TextObject("CharacterInfoUI_CasterInfo");
	m_CasterInfo->position = { -m_InfoBackground->scale.x / 2.0f + offset, m_InfoBackground->scale.y / 2.0f - offset, 0.0f };
	m_CasterInfo->fontSize = 24.0f;
	m_CasterInfo->outlineColor = AC_BLACK;
	m_CasterInfo->color = AC_WHITE;
	this->SetChildRenderFront(m_CasterInfo);

	m_EffectInfoUI[0] = new EffectInfoUI();
	m_EffectInfoUI[0]->SetEffectIconTexture("Sprites/UI/Game/Caster/ui_game_caster_status-icon.png");
	m_EffectInfoUI[0]->position.y = 0.0f;
	this->SetChildRenderFront(m_EffectInfoUI[0]);
	m_EffectInfoUI[0]->SetFitWithBorder(m_InfoBackground->scale);

	m_EffectInfoUI[1] = new EffectInfoUI();
	m_EffectInfoUI[1]->SetEffectIconTexture("Sprites/UI/Game/Caster/ui_game_caster_status-icon.png");
	m_EffectInfoUI[1]->position.y = -100.0f;
	this->SetChildRenderFront(m_EffectInfoUI[1]);
	m_EffectInfoUI[1]->SetFitWithBorder(m_InfoBackground->scale);
}

void CharacterInfoUI::UpdateSelectedCharacter(Element::Type element)
{
	switch (element)
	{
		case Element::Earth :
			m_EffectInfoUI[0]->SetActive(true);
			m_EffectInfoUI[1]->SetActive(true);

			m_EffectInfoUI[0]->SetEffectIconIndex({ 0, 4 });
			m_EffectInfoUI[0]->SetEffectInfo(EarthEffectInfo[0]);
			m_EffectInfoUI[1]->SetEffectIconIndex({ 0, 5 });
			m_EffectInfoUI[1]->SetEffectInfo(EarthEffectInfo[1]);

			m_CasterInfo->text = EarthCharacterInfo + "\n\n" + "Effect of earth spell:";
			break;
		
		case Element::Fire :
			m_EffectInfoUI[0]->SetActive(true);
			m_EffectInfoUI[1]->SetActive(true);

			m_EffectInfoUI[0]->SetEffectIconIndex({ 0, 0 });
			m_EffectInfoUI[0]->SetEffectInfo(FireEffectInfo[0]);
			m_EffectInfoUI[1]->SetEffectIconIndex({ 0, 1 });
			m_EffectInfoUI[1]->SetEffectInfo(FireEffectInfo[1]);

			m_CasterInfo->text = FireCharacterInfo + "\n\n" + "Effect of fire spell:";
			break;
		
		case Element::Water :
			m_EffectInfoUI[0]->SetActive(true);
			m_EffectInfoUI[1]->SetActive(true);

			m_EffectInfoUI[0]->SetEffectIconIndex({ 0, 2 });
			m_EffectInfoUI[0]->SetEffectInfo(WaterEffectInfo[0]);
			m_EffectInfoUI[1]->SetEffectIconIndex({ 0, 3 });
			m_EffectInfoUI[1]->SetEffectInfo(WaterEffectInfo[1]);

			m_CasterInfo->text = WaterCharacterInfo + "\n\n" + "Effect of water spell:";
			break;

		case Element::Wind :
			m_EffectInfoUI[0]->SetActive(true);
			m_EffectInfoUI[1]->SetActive(false);

			m_EffectInfoUI[0]->SetEffectIconIndex({ 0, 6 });
			m_EffectInfoUI[0]->SetEffectInfo(WindEffectInfo[0]);

			m_EffectInfoUI[0]->GetEffectInfoText()->fontSize = 22.0f;

			m_CasterInfo->text = WindCharacterInfo + "\n\n" + "Effect of wind spell:";
			break;
	}
}