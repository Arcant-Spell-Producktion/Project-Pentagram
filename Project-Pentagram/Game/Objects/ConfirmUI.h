#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"

#include "Utilities/Color.h"

class ConfirmUI : public UIObject
{
	private:
		TextObject* ConfirmText;
		Button* Yes;
		Button* No;
		Button* CloseButton;

	public:
		ConfirmUI();

		TextObject* GetConfirmText() const;
		Button* GetYesButton() const;
		Button* GetNoButton() const;
		Button* GetCloseButton() const;
};