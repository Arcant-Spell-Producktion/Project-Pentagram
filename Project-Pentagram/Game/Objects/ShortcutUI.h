#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"

#include "Game/Objects/StaticButton.h"

struct ShortcutButton : public StaticButton
		{
			UIObject* image;
			TextObject* hoverText;

			ShortcutButton(const std::string& imagePath, const std::string& hoverMessage) 
				: StaticButton("", { 80.0f, 40.0f, 1.0f })
			{
				this->SetSlicingBorderMultiplier(0.1f);

				image = new UIObject("ShortcutButton_Image");
				image->scale = { 50.0f, 25.0f, 1.0f };
				image->SetTexture(imagePath);

				hoverText = new TextObject("ShortcutButton_HoverText");
				hoverText->position.y -= 50.0f;
				hoverText->text = hoverMessage;
				hoverText->fontSize = 32.0f;
				hoverText->color = AC_WHITE;
				hoverText->outlineColor = AC_BLACK;

				this->SetChildRenderFront(image);
				this->SetChildRenderFront(hoverText);

				this->onHover.AddListener([this](Button* button) {
					hoverText->SetActive(true);
					});
				this->unHover.AddListener([this](Button* button) {
					hoverText->SetActive(false);
					});
			}
		};

class ShortcutUI : public UIObject
{
	private:

		ShortcutButton* m_PauseButton;
		ShortcutButton* m_InfoButton;
		ShortcutButton* m_HelpButton;

	public:
		ShortcutUI();

		void OnUpdate(const float& dt) override;

		ShortcutButton* GetPauseButton() const;
		ShortcutButton* GetInfoButton() const;
		ShortcutButton* GetHelpButton() const;
};