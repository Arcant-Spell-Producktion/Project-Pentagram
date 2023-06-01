#include "EffectAidUI.h"

EffectAidUI::EffectAidUI() : UIObject("EffectAidUI")
{
	this->scale = { 1920.0f, 1080.0f, 1.0f };
	this->color = AC_BLACK;

	m_Header = new TextObject("EffectAidUI_Header");
	m_Header->position = { 0.0f, 450.0f, 0.0f };
	m_Header->text = "Effect List";
	m_Header->textAlignment = TextAlignment::MID;
	m_Header->fontSize = 96.0f;
	m_Header->color = AC_WHITE;
	m_Header->outlineColor = AC_BLACK;
	this->SetChildRenderFront(m_Header);

	for (int effect = (int)SpellEffectEnum::Mark; effect <= (int)SpellEffectEnum::Boost; effect++)
	{
		m_EffectList[effect - 1] = new EffectObject((SpellEffectEnum)effect);
		m_EffectList[effect - 1]->position = m_EffectPositionList[effect - 1];
		this->SetChildRenderFront(m_EffectList[effect - 1]);
	}
}
