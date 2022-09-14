#pragma once

#include <iostream>
#include <string>

#include "Engine/UIObject.h"
#include "Engine/Button.h"

class Slider : public UIObject
{
	protected:
		Button* button;
		float m_Value;
		bool m_IsPress;

	public:
		glm::vec4 filledColor;

		Slider(const std::string& objName);
		void InitButton(Button* button);

		virtual void OnUpdate(const float& dt) override;
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		void SetValue(const float& value);
		float GetValue();
};