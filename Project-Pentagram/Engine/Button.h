#pragma once

#include "Input.h"
#include "UIObject.h"
#include "Renderer/TextObject.h"

#include <functional>

class Button : public UIObject
{
	public:
		// OnHover Color
		glm::vec4 hoverColor;
		std::function<void(Button*)> onHover;
		std::function<void(Button*)> unHover;
		std::function<void(Button*)> onClick;
		std::function<void(Button*)> onPress;
		std::function<void(Button*)> unPress;
		// Text
		TextObject textObject;
		
		Button(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;
		virtual void UnloadMesh() override;
};