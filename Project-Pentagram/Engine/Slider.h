#pragma once

#include <iostream>
#include <string>

#include "Engine/UIObject.h"
#include "Engine/Button.h"

#include "Utilities/Color.h"

class Slider : public UIObject
{
	protected:
		UIObject* m_ForeGround;
		Button* m_Button;
		float m_Value;
		bool m_IsPress;

	public:
		// ----------------- Slider Events -----------------
		std::function<void(Slider*)> onValueChanged;

		Slider(const std::string& objName);
		void InitButton();

		virtual void OnUpdate(const float& dt) override;
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		// ----------------- Getter ----------------- 
		float GetValue();
		bool IsButtonPressed();
		UIObject* GetForegroundUI();
		Button* GetSliderButton();

		// ----------------- Setter ----------------- 
		void SetValue(const float& value);
};