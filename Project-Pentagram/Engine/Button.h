#pragma once
#include "Event.h"
#include "Input.h"
#include "UIObject.h"
#include "Renderer/TextObject.h"

#include <functional>

class Button : public UIObject
{
	private:
		bool m_IsBeginHover = false;
		bool m_IsBeginUnHover = false;
	public:
		// ----------------- OnHover Color -----------------
		glm::vec4 hoverColor;

		// ----------------- Button Events -----------------
		Event<Button*> onBeginHover;
		Event<Button*> onHover;
		Event<Button*> unBeginHover;
		Event<Button*> unHover;
        Event<Button*> onClick;
		Event<Button*> onPress;
		Event<Button*> unPress;

		// ----------------- Text -----------------
		TextObject textObject;
		
		Button(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;
		virtual void UnloadMesh() override;

		void SetIsBeginHover(const bool& active);
		void SetIsBeginUnHover(const bool& active);
		bool IsBeginHover() const;
		bool IsBeginUnHover() const;
};