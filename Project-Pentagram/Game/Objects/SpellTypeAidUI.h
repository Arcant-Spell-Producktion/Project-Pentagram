#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/StaticButton.h"
#include "Game/Objects/ArrowButton.h"
#include "Game/Spells/SpellEffectType.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"

#include "Utilities/Color.h"

const std::string SpellTypeDescription[5] =
{
R"(Basic Spell:
- Engage in Spell Crashing.
- Activate upon winning Spell Crashing.)",

R"(Delayed Spell:
- Do not Engage in Spell Crashing.
- Upon Activate, Cast the Spell)",

R"(Lasting spell:
- Do not Engage in Spell Crashing.
- Once Activated, the Spell stay in effect
  for the entire duration.)",

R"(Trap spell:
- Do not Engage in Spell Crashing.
- Activate upon Any Opponent Spell
  Activate.
- Only Activate once.)",

R"(Counter spell:
- Do not Engage in Spell Crashing.
- Activate upon Opponent Spell that
  targeted the Another Unit Activate.
- Only Activate once.)"

};

class SpellTypeAidUI : public UIObject
{
	private:
		struct SpellTypeObject : public UIObject
		{
			UIObject* spell;
			UIObject* channelType;
			UIObject* border;

			TextObject* description;

			SpellTypeObject(ChannelEffectEnum channelEffect) : UIObject("SpellTypeAidObject")
			{
				float scale = 160.0f;

				this->color.a = 0.0f;

				spell = new UIObject("SpellTypeObject_Spell");
				spell->SetTexture("Sprites/UI/Game/ui_game_spell-icon_variation.png");
				spell->SetSpriteByIndex(0, 4);
				spell->scale = { scale, scale, 1.0f };

				channelType = new UIObject("SpellTypeObject_Channel");
				channelType->SetTexture("Sprites/UI/Game/ui_game_spell-icon_variation.png");
				channelType->scale = { scale, scale, 1.0f };
				channelType->color.a = 0.6f;

				border = new UIObject("SpellTypeObject_Border");
				border->SetTexture("Sprites/UI/Game/ui_game_spell-icon_border.png");
				border->scale = { scale * 114.0f / 100.0f, scale * 114.0f / 100.0f, 1.0f };

				switch (channelEffect)
				{
					case ChannelEffectEnum::None:
						border->SetSpriteByIndex(0, 0);
						channelType->color.a = 0.0f;
						break;

					case ChannelEffectEnum::Wait:
						border->SetSpriteByIndex(0, 2);
						channelType->color.a = 0.0f;
						break;

					case ChannelEffectEnum::Active:
						border->SetSpriteByIndex(0, 1);
						channelType->SetSpriteByIndex(0, 2);
						break;

					case ChannelEffectEnum::Trap:
						border->SetSpriteByIndex(0, 1);
						channelType->SetSpriteByIndex(0, 5);
						break;

					case ChannelEffectEnum::Counter:
						border->SetSpriteByIndex(0, 1);
						channelType->SetSpriteByIndex(0, 6);
						break;
				}

				spell->SetChildRenderFront(channelType);
				spell->SetChildRenderFront(border);

				description = new TextObject("SpellTypeObject_Description");
				description->text = SpellTypeDescription[(int)channelEffect];
				description->color = AC_WHITE;
				description->outlineColor = AC_BLACK;
				description->textAlignment = TextAlignment::LEFT;
				description->fontSize = 24.0f;
				description->isVCenterAlignment = true;
				description->position.x += spell->scale.x / 2.0f + 30.0f;

				this->SetChildRenderFront(spell);
				this->SetChildRenderFront(description);
			}
		};

		SpellTypeObject* m_SpellTypeList[5];
		glm::vec3 m_SpellTypePositionList[5] = {

			glm::vec3(-650.0f, 250.0f, 0.0f),
			glm::vec3( 100.0f, 250.0f, 0.0f),

			glm::vec3(-650.0f,-150.0f, 0.0f),
			glm::vec3( 100.0f, 0.0f, 0.0f),
			glm::vec3(100.0f, -250.0f, 0.0f),
		};

		TextObject* m_Header;

	public:
		SpellTypeAidUI();
};
