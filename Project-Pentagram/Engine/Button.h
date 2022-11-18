#pragma once
#include "Event.h"
#include "Input.h"
#include "UIObject.h"
#include "Renderer/TextObject.h"

#include <functional>

class Button : public UIObject
{
	public:
		// ----------------- OnHover Color -----------------
		glm::vec4 hoverColor;

		// ----------------- Button Events -----------------
		Event<Button*> onHover;
		Event<Button*> unHover;
        Event<Button*> onClick;
		Event<Button*> onPress;
		Event<Button*> unPress;

		// ----------------- Text -----------------
		TextObject textObject;
		
		Button(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;
		virtual void UnloadMesh() override;
};