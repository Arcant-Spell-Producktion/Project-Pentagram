#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"

#include "Game/Objects/StaticButton.h"

#include "Utilities/Color.h"

class ConfirmUI : public UIObject
{
	private:
		UIObject* m_Background;
		TextObject* m_ConfirmText;
		StaticButton* m_Yes;
		StaticButton* m_No;
		StaticButton* m_CloseButton;

	public:
		ConfirmUI(const glm::vec3& scale = { 750.0f, 350.0f, 1.0f });

		TextObject* GetConfirmText() const;
		Button* GetYesButton() const;
		Button* GetNoButton() const;
		Button* GetCloseButton() const;
};