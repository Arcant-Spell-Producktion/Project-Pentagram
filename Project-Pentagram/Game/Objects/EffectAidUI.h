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
R"(Marking: Unit with mark take double damage
from the next spell during this turn.)",

// Burning
R"(Burning: Unit with Burning take 10 damage per
stack at the start of the turn.
(Stack decrease by 1 after take damage))",

// Overflow
R"(Overflow: Unit with Overflow gain 1 extra
mana per stack during this battle.
(Max stack 5))",

// Freezing
R"(Freezing: Unit with Freezing use 1 more mana
per stack to decrease Cast Time, during this
turn. (Max stack 3))",

// Fortified
R"(Fortified: Unit with Fortified negate damage
from the next Spell. (Max stack 3))",

// Petrify
R"(Petrify: Spell of Unit with Petrify have 1 less
Will per stack, during this turn. (Minimum 1)
(Max stack 3))",

// Boost
R"(Boost: Gain stack(s) upon winning spell crash.
At start of the turn gain buffs based on the stacks.

2+ stack: Reduce cost for decrease Cast Time this turn by 1.

5+ stack: Reduce cost for increasing Will this turn by 1.

8 stack: Increase all Spell Damage cast this turn by 10.

Upon reaching 8 stack, during this turn no stack is gain and
the stack is reset at the end of this turn.)"

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
			glm::vec3(-400.0f,-325.0f, 0.0f),
		};

		TextObject* m_Header;

	public:
		EffectAidUI();
};