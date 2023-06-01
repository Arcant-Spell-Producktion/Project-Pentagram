#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/StaticButton.h"
#include "Game/Objects/ArrowButton.h"
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
			glm::vec3(125.0f, 300.0f, 0.0f),

			// Water Effect
			glm::vec3(-750.0f, 125.0f, 0.0f),
			glm::vec3(125.0f, 125.0f, 0.0f),

			// Earth Effect
			glm::vec3(-750.0f, -50.0f, 0.0f),
			glm::vec3(125.0f, -50.0f, 0.0f),

			// Wind Effect
			glm::vec3(-300.0f,-325.0f, 0.0f),
		};

		TextObject* m_Header;

	public:
		EffectAidUI();
};