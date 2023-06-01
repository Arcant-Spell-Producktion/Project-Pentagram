#include "SpellTypeAidUI.h"

SpellTypeAidUI::SpellTypeAidUI() : UIObject("SpellTypeAidUI")
{
	this->scale = { 1920.0f, 1080.0f, 1.0f };
	this->color = AC_BLACK;

	m_Header = new TextObject("EffectAidUI_Header");
	m_Header->position = { 0.0f, 450.0f, 0.0f };
	m_Header->text = "Spell Type List";
	m_Header->textAlignment = TextAlignment::MID;
	m_Header->fontSize = 96.0f;
	m_Header->color = AC_WHITE;
	m_Header->outlineColor = AC_BLACK;
	this->SetChildRenderFront(m_Header);

	for (int channel = (int)ChannelEffectEnum::None; channel <= (int)ChannelEffectEnum::Counter; channel++)
	{
		m_SpellTypeList[channel] = new SpellTypeObject((ChannelEffectEnum)channel);
		m_SpellTypeList[channel]->position = m_SpellTypePositionList[channel];
		this->SetChildRenderFront(m_SpellTypeList[channel]);
	}
}