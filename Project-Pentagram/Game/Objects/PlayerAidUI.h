#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/Objects/ScrollButton.h"
#include "Game/Spells/SpellEffectType.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"

#include "Utilities/Color.h"

const std::string EffectDescription[7] =
{
// Marking
R"(Marking: Unit with mark effect take double
damage from the next spell.)",

// Burning
R"(Burning: Unit with burning will take 10 damage
per stack at the start of the turn.
(Stack decrease by 1 after take damage))",

// Overflow
R"(Overflow: Unit with Overflow gain an extra
mana during this battle (Maximum at 5))",

// Freezing
R"(Freezing: Unit with Freezing will use 1 more
mana to adjust cast time.
(this effect is stackable))",

// Fortified
R"(Fortified: Unit with fortified effect negate
damage from spell (max stack 3))",

// Petrify
R"(Petrify: Unit with petrify will have 1 less will for
each spell (can't go below 1))",

// Boost
R"(Boost: When a spell wins in a Will Compare sequence
gain a stack. On next turn gain a buff based on how
many stacks you have.

2+ stack: Reduce cost for changing Cast time this
turn by 1

5+ stack: Reduce cost for changing WILL this turn
by 1

8+ stack: Damage from spell +10.
(At the start of next turn boost stack become 0))"

};

const std::string SpellDescription[5] =
{
R"(claiming wave: heal player hp when this spell
is casted sucessfully.)",

R"(Unbreakable shield: Ignore all damage during
spell activation actitation.)",

R"(Earth prison: during activation destroy all the
enemies spell in the first time track on
contract.)",

R"(Reflect shield: During activation destroy an
enemies spell that target the witch and reflect
the damage to the enemies.)",

R"(Fairy trick: During activation shift all the
enemies spell in the time track backward by
one track.)"
};

struct BackButton : public ScrollButton
{
	UIObject* ArrowSprite;

	BackButton() : ScrollButton("BackButton")
	{
		this->textObject.text = "";

		ArrowSprite = new UIObject("BackButton_ArrowSprite");
		ArrowSprite->scale = { 140.0f, 90.0f, 1.0f };
		ArrowSprite->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_scroll_button-arrow.png");
		ArrowSprite->SetSpriteByIndex(1, 0);
		this->SetChildRenderFront(ArrowSprite);
	}
};

class EffectAidUI : public UIObject
{
	private:
		struct EffectObject : public UIObject
		{
			UIObject* EffectIcon;
			TextObject* EffectDetail;

			EffectObject(SpellEffectEnum effectEnum) : UIObject("Effect_Aid_Object_" + SpellEffectType::GetString(effectEnum))
			{
				this->color.a = 0.0f;

				EffectIcon = new UIObject("Effect_Icon");
				EffectIcon->scale = { 160.0f, 160.0f, 1.0f };
				EffectIcon->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_status-icon.png");
				EffectIcon->SetSpriteByIndex(0, (int)effectEnum - 1);
				this->SetChildRenderFront(EffectIcon);

				EffectDetail = new TextObject("Effect_Detail");
				EffectDetail->position.x += EffectIcon->scale.x / 2.0f + 30.0f;
				EffectDetail->text = EffectDescription[(int)effectEnum - 1];
				EffectDetail->textAlignment = TextAlignment::LEFT;
				EffectDetail->fontSize = 24.0f;
				EffectDetail->color = AC_WHITE;
				EffectDetail->outlineColor = AC_BLACK;
				EffectDetail->isVCenterAlignment = true;
				this->SetChildRenderFront(EffectDetail);
			}
		};

		EffectObject* m_EffectList[7];
		glm::vec3 m_EffectPositionList[7] = {

			// Fire Effect
			glm::vec3(-750.0f, 300.0f, 0.0f),
			glm::vec3( 125.0f, 300.0f, 0.0f),

			// Water Effect
			glm::vec3(-750.0f, 125.0f, 0.0f),
			glm::vec3( 125.0f, 125.0f, 0.0f),

			// Earth Effect
			glm::vec3(-750.0f, -50.0f, 0.0f),
			glm::vec3( 125.0f, -50.0f, 0.0f),

			// Wind Effect
			glm::vec3(-300.0f,-325.0f, 0.0f),
		};

		TextObject* m_Header;
		TextObject* m_PressF1;
		BackButton* m_BackButton;

	public:
		EffectAidUI() : UIObject("EffectAidUI")
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

			m_PressF1 = new TextObject("EffectAidUI_PressF1");
			m_PressF1->position = { -800.0f, -475.0f, 0.0f };
			m_PressF1->text = "Press F1 to go back";
			m_PressF1->textAlignment = TextAlignment::MID;
			m_PressF1->fontSize = 24.0f;
			m_PressF1->color = AC_WHITE;
			m_PressF1->outlineColor = AC_BLACK;
			this->SetChildRenderFront(m_PressF1);

			m_BackButton = new BackButton();
			m_BackButton->position = { 800.0f, -425.0f, 0.0f };
			this->SetChildRenderFront(m_BackButton);

			for (int effect = (int)SpellEffectEnum::Mark; effect <= (int)SpellEffectEnum::Boost; effect++)
			{
				m_EffectList[effect - 1] = new EffectObject((SpellEffectEnum)effect);
				m_EffectList[effect - 1]->position = m_EffectPositionList[effect - 1];
				this->SetChildRenderFront(m_EffectList[effect - 1]);
			}
		}

		BackButton* GetButton() const { return m_BackButton; };
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
					case 0: spell->SetChannelEffectType(ChannelEffectEnum::Wait); break;
					case 1: spell->SetChannelEffectType(ChannelEffectEnum::Active); break;
					case 2: spell->SetChannelEffectType(ChannelEffectEnum::Trap); break;
					case 3: spell->SetChannelEffectType(ChannelEffectEnum::Counter); break;
					case 4: spell->SetChannelEffectType(ChannelEffectEnum::Active); break;
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
			// Water Spell
			glm::vec3(-750.0f, 200.0f, 0.0f),

			// Earth Spell
			glm::vec3( 125.0f, 200.0f, 0.0f),
			glm::vec3(-750.0f, -50.0f, 0.0f),
			glm::vec3( 125.0f, -50.0f, 0.0f),

			// Wind Spell
			glm::vec3(-300.0f,-325.0f, 0.0f),
		};

		TextObject* m_Header;
		TextObject* m_PressF1;
		BackButton* m_BackButton;

	public:
		SpellAidUI() : UIObject("SpellAidUI")
		{
			this->scale = { 1920.0f, 1080.0f, 1.0f };
			this->color = AC_BLACK;

			m_Header = new TextObject("SpellAidUI_Header");
			m_Header->position = { 0.0f, 450.0f, 0.0f };
			m_Header->text = "Specials Spell List";
			m_Header->textAlignment = TextAlignment::MID;
			m_Header->fontSize = 96.0f;
			m_Header->color = AC_WHITE;
			m_Header->outlineColor = AC_BLACK;
			this->SetChildRenderFront(m_Header);

			m_PressF1 = new TextObject("SpellAidUI_PressF1");
			m_PressF1->position = { 800.0f, -475.0f, 0.0f };
			m_PressF1->text = "Press F1 to go back";
			m_PressF1->textAlignment = TextAlignment::MID;
			m_PressF1->fontSize = 24.0f;
			m_PressF1->color = AC_WHITE;
			m_PressF1->outlineColor = AC_BLACK;
			this->SetChildRenderFront(m_PressF1);

			m_BackButton = new BackButton();
			m_BackButton->position = { -800.0f, -425.0f, 0.0f };
			m_BackButton->ArrowSprite->scale.x *= -1.0f;
			this->SetChildRenderFront(m_BackButton);

			for (int idx = 0; idx < 5; idx++)
			{
				switch (idx) 
				{
					case 0: m_SpellList[idx] = new SpellObject(Element::Water, 4, idx); break;
					case 1: m_SpellList[idx] = new SpellObject(Element::Earth, 7, idx); break;
					case 2: m_SpellList[idx] = new SpellObject(Element::Earth, 5, idx); break;
					case 3: m_SpellList[idx] = new SpellObject(Element::Earth, 6, idx); break;
					case 4: m_SpellList[idx] = new SpellObject(Element::Wind, 6, idx); break;
				}
				
				m_SpellList[idx]->position = m_SpellPositionList[idx];
				this->SetChildRenderFront(m_SpellList[idx]);
			}
		}

		BackButton* GetButton() const { return m_BackButton; };
};

class PlayerAidUI : public UIObject
{
	private:
		EffectAidUI* m_EffectAidUI;
		SpellAidUI* m_SpellAidUI;
	public:
		PlayerAidUI() : UIObject("PlayerAidUI")
		{
			this->color.a = 0.0f;

			m_EffectAidUI = new EffectAidUI();
			m_SpellAidUI = new SpellAidUI();

			m_EffectAidUI->GetButton()->onClick = [this](Button* button)
			{
				m_SpellAidUI->SetActive(true);
				m_EffectAidUI->SetActive(false);
			};
			m_SpellAidUI->GetButton()->onClick = [this](Button* button)
			{
				m_EffectAidUI->SetActive(true);
				m_SpellAidUI->SetActive(false);
			};

			this->SetChildRenderFront(m_EffectAidUI);
			this->SetChildRenderFront(m_SpellAidUI);

			this->SetActive(false);
		}

		void ToggleEvent()
		{
			if (!this->IsActive())
			{
				this->SetActive(true);

				m_EffectAidUI->SetActive(true);
				m_SpellAidUI->SetActive(false);
			}
			else
			{
				this->SetActive(false);
			}
		}

};