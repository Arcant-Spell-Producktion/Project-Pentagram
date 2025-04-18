#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/StaticButton.h"
#include "Game/Objects/ArrowButton.h"
#include "Game/Spells/SpellEffectType.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"

#include "Utilities/Color.h"

const std::string SpellDescription[4] =
{

R"(Unbreakable shield: Ignore all damage during
spell activation.)",

R"(Earth prison: Upon Activation, cancel all the
enemy spells in the TimeTrack.)",

R"(Reflect shield: Upon Activation, cancel the
spell that activate it, and reflect the damage.)",

R"(Fairy trick: Upon Activation, decrease the
enemy spell's Cast Time by one.)"

};

class SpellAidUI : public UIObject
{
	private:
		struct SpellObject : public UIObject
		{
			SpellIconUI* SpellIcon;
			TextObject* SpellDetail;
			CastSpellDetail* spellDetail;
			Spell* spell;

			SpellObject(Element::Type element, int spellIndex, int spellOrder) : UIObject("Spell_Aid_Object_")
			{
				this->color.a = 0.0f;

				spell = new Spell(element, spellIndex);
				switch (spellOrder)
				{
					case 0: spell->SetChannelEffectType(ChannelEffectEnum::Active); break;
					case 1: spell->SetChannelEffectType(ChannelEffectEnum::Trap); break;
					case 2: spell->SetChannelEffectType(ChannelEffectEnum::Counter); break;
					case 3: spell->SetChannelEffectType(ChannelEffectEnum::Trap); break;
				}
				spellDetail = new CastSpellDetail(CasterPosition::CasterA, spell, 0, 0);

				SpellIcon = new SpellIconUI("Spell_Icon" + Element::GetString(element) + std::to_string(spellIndex));
				SpellIcon->SetIcon(spellDetail, true);
				SpellIcon->SetTransparency(true);
				SpellIcon->SetOverlayToggle(true);
				SpellIcon->SetScale({ 170.0f, 170.0f, 1.0f });
				this->SetChildRenderFront(SpellIcon);

				SpellDetail = new TextObject("Effect_Detail");
				SpellDetail->position.x += SpellIcon->scale.x / 2.0f + 30.0f;
				SpellDetail->text = SpellDescription[spellOrder];
				SpellDetail->textAlignment = TextAlignment::LEFT;
				SpellDetail->fontSize = 24.0f;
				SpellDetail->color = AC_WHITE;
				SpellDetail->outlineColor = AC_BLACK;
				SpellDetail->isVCenterAlignment = true;
				this->SetChildRenderFront(SpellDetail);
			}
			~SpellObject()
			{
				delete spellDetail;
				delete spell;
			}
		};

		SpellObject* m_SpellList[5];
		glm::vec3 m_SpellPositionList[5] = {
			// Earth Spell
			glm::vec3(-750.0f, 200.0f, 0.0f),
			glm::vec3(125.0f, 200.0f, 0.0f),
			glm::vec3(-750.0f, -50.0f, 0.0f),

			// Wind Spell
			glm::vec3(125.0f, -50.0f, 0.0f),
		};

		TextObject* m_Header;

	public:
		SpellAidUI();
};