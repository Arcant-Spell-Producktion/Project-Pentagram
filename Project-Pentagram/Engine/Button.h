#pragma once

#include "Input.h"
#include "UIObject.h"
#include "Renderer/TextObject.h"

class Button : public UIObject
{
	public:
		// Text
		TextObject textObject;
		// Button Border(Button Slicing)
		float border;
		// Pointer of Vector (Tracking Current Object in UIObjectList)
		std::vector<UIObject*>* uiList;
		
		Button(const std::string& objName);
		virtual void Draw(Camera& camera, const glm::mat4& parentModel = glm::mat4(1.0f)) override;
		bool onClick();
		bool onHover();
};